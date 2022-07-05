#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/LaneArray.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include "BehaviorStateMachine.h"
#include <cmath>


class DecisionMaker
{
    private:
        bool start, isFront, isLag, isLead, needLC, psbLC, doneLC, isEmergency;
        float gapFront, gapLead, gapLag;
        BehaviorStateMachine behaviorfsm;
        void calculateLon(int n, float* psarr, hmcl_msgs::Lane &lane){
            for(int i = 1; i < n; i++){
                float d = sqrt(pow(lane.waypoints[i].pose.pose.position.x - lane.waypoints[i-1].pose.pose.position.x,2)+pow(lane.waypoints[i].pose.pose.position.y - lane.waypoints[i-1].pose.pose.position.y,2));
                psarr[i] = psarr[i-1] + d;
            }
        }

        void calculateFrenet(int n, float* psarr, float px, float py, float vx, float vy, float* psl, hmcl_msgs::Lane &lane){
            float mindist = 100;
            int minidx = 0;
            float mindist2 = 100;
            int minidx2 = 0;
            int idx = 0;
            for(int i = 0; i < n; i++){
                float dist = sqrt(pow(px - lane.waypoints[i].pose.pose.position.x,2)+pow(py - lane.waypoints[i].pose.pose.position.y,2));
                if(dist<mindist){
                    mindist2 = mindist;
                    minidx2 = minidx;
                    mindist = dist;
                    minidx = i;
                }
                if(minidx < minidx2) idx = minidx;
                else idx = minidx2;
            }
            
            float x[2] = {px - lane.waypoints[idx].pose.pose.position.x, py - lane.waypoints[idx].pose.pose.position.y};
            float p[2] = {lane.waypoints[idx+1].pose.pose.position.x - lane.waypoints[idx].pose.pose.position.x, lane.waypoints[idx+1].pose.pose.position.y - lane.waypoints[idx].pose.pose.position.y};
            float v[2] = {vx, vy};
            float dp = sqrt(pow(p[0],2)+pow(p[1],2));
            float dx = sqrt(pow(x[0],2)+pow(x[1],2));
            float sv = sqrt(pow(v[0],2)+pow(v[1],2));
            float theta = acos((x[0]*p[0]+x[1]*p[1])/(dx*dp));
            float theta2 = acos((v[0]*p[0]+v[1]*p[1])/(sv*dp));
            float s = psarr[idx]+dx*cos(theta);
            float ds = sv*cos(theta2);
            float l;
            float dl;
            //ROS_INFO("idx %d, x %d, p %d, v %d", idx, x[0],p[0],v[0]);
            if(x[0]*p[1]-x[1]*p[0]<0) l = -dx*sin(theta);
            else l = dx*sin(theta);
            if(v[0]*p[1]-v[1]*p[0]<0) dl = -sv*sin(theta2);
            else dl = sv*sin(theta2);
            psl[0] = s;
            psl[1] = l;
            psl[2] = ds;
            psl[3] = dl;
        }

        void calculateSafeDistance(float vFront, float vRear, float &dSafe){
            const float minBrake = 2, maxBrake = 5, maxAccel = 3, rho = 1;
            dSafe = vRear*rho + (1/2)*maxAccel*pow(rho,2) + pow((vRear + rho*maxAccel),2)/(2*minBrake) - pow(vFront,2)/(2*maxBrake);
        }
    public:
        DecisionMaker(){
            this->start = true; // will update after mission planning is done
            this->isFront = false;
            this->isLag = false;
            this->isLead = false;
            this->needLC = false;
            this->psbLC = false;
            this->doneLC = false;
            this->isEmergency = false;
            this->gapFront = 100;
            this->gapLead = 100;
            this->gapLag = 100;
        }

        void updateParameter(hmcl_msgs::LaneArray &globalLaneArray, autoware_msgs::DetectedObjectArray &detectedObjects, geometry_msgs::Pose &egoPose, geometry_msgs::Twist &egoVel){
            int n0 = globalLaneArray.lanes[0].waypoints.size();
            int n1 = 1;
            float sarr0[n0];
            float slEgo[4], slObj[4];
            int on = detectedObjects.objects.size();
            float sObj[on], lObj[on], dsObj[on], dlObj[on], laneidObj[on];
            float sEgo, dsEgo, lEgo, dlEgo, wLane = 3.5, lenEgo = 4.180, frontlenEgo = 4.180/2;// need to check lidar position in real vehicle
            float* psarr;
            float* psl;
            this->isFront = false;
            this->isLag = false;
            this->isLead = false;
            this->psbLC = false;
            this->isEmergency = false;
            float safeFront = 100, safeLead = 100,safeLag = 100, gapFront = 100, gapLead = 100, gapLag = 100;
            int idFront, idLead, idLag;
            bool checkLag = false, checkLead = false;
            float xObj[on],yObj[on],vxObj[on],vyObj[on];

            float yaw = atan2(2.0*(egoPose.orientation.y*egoPose.orientation.z + egoPose.orientation.w*egoPose.orientation.x), 1-2*(egoPose.orientation.w*egoPose.orientation.w + egoPose.orientation.z*egoPose.orientation.z));
            for(int i = 0; i < on; i++){
                //ROS_INFO("%f, %f",egoPose.position.x, egoPose.position.y);
                xObj[i] = egoPose.position.x + detectedObjects.objects[i].pose.position.x*cos(yaw)-detectedObjects.objects[i].pose.position.y*sin(yaw);
                yObj[i] = egoPose.position.y + detectedObjects.objects[i].pose.position.x*sin(yaw)+detectedObjects.objects[i].pose.position.y*cos(yaw);
                vxObj[i] = detectedObjects.objects[i].velocity.linear.x*cos(yaw) - detectedObjects.objects[i].velocity.linear.y*sin(yaw);
                vyObj[i] = detectedObjects.objects[i].velocity.linear.x*sin(yaw) + detectedObjects.objects[i].velocity.linear.y*cos(yaw);
                //ROS_INFO("i:%d,x: %f,y: %f,vx: %f,vy: %f",i,xObj[i],yObj[i],vxObj[i],vxObj[i]);
            }


            // calculate Frenet longitudinal length of egolane            
            psarr = sarr0;
            this->calculateLon(n0, psarr, globalLaneArray.lanes[0]);

            // calculate Frenet coordinate of ego vehicle
            psl = slEgo;
            this->calculateFrenet(n0, psarr, egoPose.position.x, egoPose.position.y, egoVel.linear.x, egoVel.linear.y, psl, globalLaneArray.lanes[0]);
            sEgo = slEgo[0];
            lEgo = slEgo[1];
            dsEgo = slEgo[2];
            dlEgo = slEgo[3];
            // ROS_INFO("slego, x: %f,y: %f,vx: %f,vy: %f",sEgo,lEgo,dsEgo,dlEgo);
            // determine the necessity of lane change
            // ROS_INFO("n1: %d",globalLaneArray.lanes.size());
            if(globalLaneArray.lanes.size() > 1){
                this->needLC = true;
                n1 = globalLaneArray.lanes[1].waypoints.size();
            }
            else{
                this->needLC = false;
            }

            // calculate Frenet longitudinal length of target lane
            float sarr1[n1];
            if(this->needLC == true){
                psarr = sarr1;
                this->calculateLon(n1, psarr, globalLaneArray.lanes[1]);
            }

            // calculate Frenet coordinate of objects
            psl = slObj;
            int minFront = 100; // need to check if it can be larger than 100 and find proper value
            int minLead = 100;
            int minLag = 100;
            for(int i = 0; i < on; i++){
                laneidObj[i] = 100;
                for(int j = 0; j < 2; j++){
                    if(j == 0){
                        psarr = sarr0;
                        this->calculateFrenet(n0, psarr, xObj[i], yObj[i], vxObj[i], vyObj[i], psl, globalLaneArray.lanes[0]);
                        sObj[i] = slObj[0];
                        lObj[i] = slObj[1];
                        dsObj[i] = slObj[2];
                        dlObj[i] = slObj[3];
                        if(abs(lObj[i]) <= wLane/2) laneidObj[i] = 0;
                    }
                    else if(j == 1){
                        if(this->needLC == true){
                            psarr = sarr1;
                            this->calculateFrenet(n1, psarr, xObj[i], yObj[i], vxObj[i], vyObj[i], psl, globalLaneArray.lanes[1]);
                            if(abs(slObj[1]) < abs(lObj[i]) && abs(slObj[1]) <= wLane/2){
                                laneidObj[i] = 1;
                            }
                        }
                    }
                }
                if(laneidObj[i] == 0){
                    // behind vehicle
                    if(sObj[i]-sEgo < 0) break;
                    // front vehicle
                    else{
                        if(sObj[i]-sEgo < minFront){
                            idFront = i;
                            minFront = sObj[i]-sEgo;
                            this->isFront = true;
                        }
                    }
                }
                else if(laneidObj[i] == 1){
                    // lag vehicle
                    if(sObj[i]-sEgo < 0){
                        if(sEgo-sObj[i] < minLag){
                            idLag = i;
                            minLag = sEgo-sObj[i];
                            this->isLag = true;
                        }
                    }
                    // lead vehicle
                    else{
                        if(sObj[i]-sEgo < minLead){
                            idLead = i;
                            minLead = sObj[i]-sEgo;
                            this->isLead = true;
                        }
                    }
                }
                // ROS_INFO("slobj, i:%d,x: %f,y: %f,vx: %f,vy: %f",i,sObj[i],lObj[i],dsObj[i],dlObj[i]);
            }

            // calculate safe distance
            if(this->isFront){
                this->calculateSafeDistance(dsObj[idFront],dsEgo,safeFront);
                gapFront = minFront - detectedObjects.objects[idFront].dimensions.x/2 - frontlenEgo;
            }
            if(needLC){
                if(this->isLag){
                    this->calculateSafeDistance(dsEgo,dsObj[idLag],safeLag);
                    gapLag = minLag - detectedObjects.objects[idLag].dimensions.x/2 - (lenEgo-frontlenEgo);
                    if(gapLag > safeLag) checkLag = true;
                }
                else checkLag = true;
                if(this->isLead){
                    this->calculateSafeDistance(dsObj[idLead],dsEgo,safeLead);
                    gapLead = minLead - detectedObjects.objects[idLead].dimensions.x/2 - frontlenEgo;
                    if(gapLead > safeLead) checkLead = true;
                }
                else checkLead = true;
                if(checkLead && checkLag) this->psbLC = true;
            }

            // determine doneLC
            if(this->getCurrentBehavior() == BehaviorState::LaneChange){
                if(this->needLC == false && abs(lEgo)<0.5) this->doneLC = true; // need to check if 0.5 is sufficient
            }
        }

        void updateBehaviorState(){
            behaviorfsm.updateBehaviorState(this->start, this->isFront, this->needLC, this->psbLC, this->doneLC, this->isEmergency);
        }

        bool getParam(int param_id){
            if(param_id == 1) return start;
            else if(param_id == 2) return isFront;
            else if(param_id == 3) return needLC;
            else if(param_id == 4) return psbLC;
            else if(param_id == 5) return doneLC;
            else if(param_id == 6) return isEmergency;
        }

        BehaviorState getCurrentBehavior(){
            return behaviorfsm.getCurrentBehavior();
        }
};


