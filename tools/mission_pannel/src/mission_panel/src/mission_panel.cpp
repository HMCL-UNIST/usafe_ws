
//   Copyright (c) 2022 Ulsan National Institute of Science and Technology (UNIST)
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

//   Authour : Hojin Lee, hojinlee@unist.ac.kr

#include <stdio.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QSignalMapper>
#include <QTimer>
#include <QVBoxLayout>
#include <QMap>

#include <geometry_msgs/Twist.h>

#include <std_msgs/String.h>
#include "mission_panel.h"

namespace trafficsim_rviz
{
// BEGIN_TUTORIAL
// Here is the implementation of the DecisionMakerPanel class.  DecisionMakerPanel
// has these responsibilities:
//
// - Act as a container for GUI elements DriveWidget and QLineEdit.
// - Publish command velocities 10 times per second (whether 0 or not).
// - Saving and restoring internal state from a config file.
//
// We start with the constructor, doing the standard Qt thing of
// passing the optional *parent* argument on to the superclass
// constructor, and also zero-ing the velocities we will be
// publishing.

class StateInfo
{
private:
public:
  uint64_t state_num_;
  uint8_t state_category_;
  std::string state_num_name_;
  std::string state_category_name_;
};

MissionPanel::MissionPanel(QWidget* parent) : rviz::Panel(parent)
{
  statecmd_publisher_ = nh_.advertise<std_msgs::String>("/mission_cmd", 1);

  // Next we lay out the "output topic" text entry field using a
  // QLabel and a QLineEdit in a QHBoxLayout.
  QGridLayout* label_layout = new QGridLayout;
  label_layout->addWidget(new QLabel("Mission Panel"), 0, 0);

  QSignalMapper* signalMapper = new QSignalMapper(this);
  connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(sendTopic(QString)));

  QMap<QString, QPushButton*> buttons_def;
  // mission Row1
  buttons_def["SpeedBump"] = new QPushButton("\nSpeedBump\n");
  signalMapper->setMapping(buttons_def["SpeedBump"], QString("SpeedBump"));
  buttons_def["Dropping"] = new QPushButton("\nDropping\n");
  signalMapper->setMapping(buttons_def["Dropping"], QString("Dropping"));
  buttons_def["Blind"] = new QPushButton("\nBlind\n");
  signalMapper->setMapping(buttons_def["Blind"], QString("Blind"));
  // mission Row2
  buttons_def["Overtaking"] = new QPushButton("Overtaking");
  signalMapper->setMapping(buttons_def["Overtaking"], QString("Overtaking"));
  buttons_def["Pedestrian"] = new QPushButton("Pedestrian");
  signalMapper->setMapping(buttons_def["Pedestrian"], QString("Pedestrian"));
  buttons_def["Pedestrian_2"] = new QPushButton("Pedestrian_2");
  signalMapper->setMapping(buttons_def["Pedestrian_2"], QString("Pedestrian_2"));
  // Row3
  buttons_def["Bike"] = new QPushButton("Bike");
  signalMapper->setMapping(buttons_def["Bike"], QString("Bike"));
  buttons_def["Clear"] = new QPushButton("Clear");
  signalMapper->setMapping(buttons_def["Clear"], QString("Clear"));
  buttons_def["All"] = new QPushButton("All");
  signalMapper->setMapping(buttons_def["All"], QString("All"));
  // set options
  QMap<QString, QPushButton*>::const_iterator i = buttons_def.constBegin();
  QFont* q_font = new QFont("Arial", 11);
  QSizePolicy* q_size_policy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  while (i != buttons_def.constEnd())
  {
    i.value()->setSizePolicy(*q_size_policy);
    i.value()->setFont(*q_font);
    connect(i.value(), SIGNAL(clicked()), signalMapper, SLOT(map()));
    ++i;
  }

  QGridLayout* button_layout_main = new QGridLayout;
  button_layout_main->addWidget(new QLabel("Missions"), 0, 0);
  button_layout_main->addWidget(buttons_def["SpeedBump"], 1, 0);
  button_layout_main->addWidget(buttons_def["Dropping"], 1, 1);
  button_layout_main->addWidget(buttons_def["Blind"], 1, 2);
  button_layout_main->addWidget(buttons_def["Overtaking"], 2, 0);
  button_layout_main->addWidget(buttons_def["Pedestrian"], 2, 1);
  button_layout_main->addWidget(buttons_def["Pedestrian_2"], 2, 2);
  button_layout_main->addWidget(buttons_def["Bike"], 3, 0);
  button_layout_main->addWidget(buttons_def["Clear"], 3, 2);
  button_layout_main->addWidget(buttons_def["All"], 3, 1);

  QVBoxLayout* layout = new QVBoxLayout;
  layout->addLayout(label_layout);
  layout->addLayout(button_layout_main);
  setLayout(layout);
}

void MissionPanel::sendTopic(const QString &text)
{
  std_msgs::String msg;
  msg.data = text.toStdString();
  statecmd_publisher_.publish(msg);
}

void MissionPanel::save(rviz::Config config) const
{
  rviz::Panel::save(config);
}

void MissionPanel::load(const rviz::Config& config)
{
  rviz::Panel::load(config);
}

}  // 

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(trafficsim_rviz::MissionPanel, rviz::Panel)
