int32 item_id
int32 item_type     # 0 : laptime minus, 1 : laptime plus, 2: boost
int32 item_status   # 0 : get(true), 1 : get(false)
int32 score         # 0 : unavailable(boost), (+) : laptime minus (score up), (+) laptime plus (score down)
int32 speed         # 0 : stop, 1~254 : max speed, 255 : unavailable(item) 
int32 duration      # 0 : finish, 1~253 : left time, 254 : until final, 255 : unavailable(item) 
float64 pos_lat       
float64 pos_long
int32 extend        # meter (circle)
