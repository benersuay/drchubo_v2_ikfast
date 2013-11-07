drchubo_v2_ikfast
==============

IKfast inverse kinematics solvers for DRCHubo v2 model with a plugin wrapper for OpenRAVE. The plugin wrapper means that the IKfast solvers are location-independent provided they are in your OPENRAVE_PLUGINS path.

Build and usage instructions
----------------------------
First, clone this repository:
```
$ cd /your/catkin/workspace/src
$ git clone https://github.com/benersuay/drchubo_v2_ikfast.git
$ rospack profile
```

To build all packages in this repository:
```
(in the surrounding Catkin workspace directory)
$ catkin_make
```

To build a particular package in the repository:
```
(in the surrounding Catkin workspace directory)
$ catkin_make --pkg <package name>
```

To use, you must update your `OPENRAVE_PLUGINS` environment variable:
```
$ roscd drchubo_v2_ikfast/plugins
```
Add the current directory to `OPENRAVE_PLUGINS`:
```
$ export OPENRAVE_PLUGINS=$PWD:$OPENRAVE_PLUGINS
```
(If you would like to do this in your `.bashrc` file, then instead of $PWD just add the full path of your drchubo_v2_ikfast/plugins directory.)

Next, you need to edit the `drchubo_v2.robot.xml` model to use the new IK solvers. The new file should look like this:
```
<?xml version="1.0" encoding="utf-8"?>
<Robot name="drchubo_v2" >
    <KinBody file="drchubo_v2.kinbody.xml" makejoinedlinksadjacent="true">
    	<translation>0 0 0.962</translation>
    </KinBody>

    <Manipulator name="leftArm">
        <base>Body_Torso</base>
        <effector>leftPalm</effector>
        <direction>0 1 0</direction>
        <iksolver>drchubo_v2_leftarm_ikfast</iksolver>
    </Manipulator>

    <Manipulator name="rightArm">
        <base>Body_Torso</base>
        <effector>rightPalm</effector>
        <direction>0 1 0</direction>
        <iksolver>drchubo_v2_rightarm_ikfast</iksolver>
    </Manipulator>

    <Manipulator name="leftFoot">
        <base>Body_TSY</base>
        <effector>leftFoot</effector>
        <direction>0 0 -1</direction>
        <iksolver>drchubo_v2_leftleg_ikfast</iksolver>
    </Manipulator>

    <Manipulator name="rightFoot">
        <base>Body_TSY</base>
        <effector>rightFoot</effector>
        <direction>0 0 -1</direction>
        <iksolver>drchubo_v2_rightleg_ikfast</iksolver>
    </Manipulator>

    <Manipulator name="Head">
        <base>Body_Torso</base>
        <effector>Body_NK2</effector>
        <direction>0 0 1</direction>
    </Manipulator>

</Robot>
```
After you finish all of the steps above. If you edited your .bashrc file, source it with
```
. ~/.bashrc
```

catkin_make the drchubo_v2_ikfast package, and once it's done, use the following command to see if the plugins are visible to OpenRAVE:
```
openrave --listplugins
```
In the iksolver section of the list, if you see following solvers: 
```
drchubo_v2_leftarm_ikfast - /your/path/to/catkin_ws/src/drchubo_v2_ikfast/plugins/libdrchubo_v2_ikfast.so
drchubo_v2_leftleg_ikfast - /your/path/to/catkin_ws/src/drchubo_v2_ikfast/plugins/libdrchubo_v2_ikfast.so
drchubo_v2_rightarm_ikfast - /your/path/to/catkin_ws/src/drchubo_v2_ikfast/plugins/libdrchubo_v2_ikfast.so
drchubo_v2_rightleg_ikfast - /your/path/to/catkin_ws/src/drchubo_v2_ikfast/plugins/libdrchubo_v2_ikfast.so
```
it means that you successfully installed the plugin and it is visible to OpenRAVE.

Finally try running the test script to see if it works:
```
rosrun drchubo_v2_ikfast test.py
```

You should see the robot with all its manipulators 10 cms above their initial location in the world.

