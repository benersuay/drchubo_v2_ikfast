#!/usr/bin/env python
# Ben Suay, RAIL
# benersuay@wpi.edu
# November, 2007
# Worcester Polytechnic Institute

import roslib.packages
from openravepy import *
import sys
if not __openravepy_build_doc__:
    from openravepy import *
    from numpy import *
    import numpy
import time
import os # for file operations

def ikfast(robot, manipname, T):
    robot.SetActiveManipulator(manipname)
    ikmodel = databases.inversekinematics.InverseKinematicsModel(robot,iktype=IkParameterizationType.Transform6D)
    ikmodel.load()

    # check if ik solution(s) exist    
    return ikmodel.manip.FindIKSolution(array(T),IkFilterOptions.CheckEnvCollisions)

def run():
    env = Environment()
    RaveSetDebugLevel(DebugLevel.Info) # set output level to debug
    packagepath=roslib.packages.get_pkg_dir("drchubo_v2")
    modelpath=packagepath+"/robots/drchubo_v2.robot.xml"
    robot = env.ReadRobotURI(modelpath)
    env.Add(robot)
    env.SetViewer('qtcoin')

    # do it for both hands
    for i in range(4):
        manip = robot.GetManipulators()[i]
        T0_Hand = manip.GetEndEffectorTransform()
        T0_Hand[2,3] += 0.1 # add 10 cms to where the hand is
        sol = ikfast(robot, manip.GetName(), T0_Hand)
        print sol
        if (sol is not None):
            robot.SetDOFValues(sol, manip.GetArmIndices())

    print "Press Enter to exit..."
    sys.stdin.readline()
    env.Destroy()
    RaveDestroy()

if __name__ == "__main__":
    run()
