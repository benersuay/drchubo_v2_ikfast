// -*- coding: utf-8 -*-
// Copyright (C) 2006-2012 Rosen Diankov <rosen.diankov@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "plugindefs.h"
#include <openrave/plugin.h>

namespace drchubo_v2_leftarm_ikfast { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
namespace drchubo_v2_rightarm_ikfast { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
namespace drchubo_v2_leftleg_ikfast { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
namespace drchubo_v2_rightleg_ikfast { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }

IkSolverBasePtr CreateIkSolverFromName(const string& _name, const std::vector<dReal>& vfreeinc, EnvironmentBasePtr penv);
ModuleBasePtr CreateIkFastModule(EnvironmentBasePtr penv, std::istream& sinput);
void DestroyIkFastLibraries();

InterfaceBasePtr CreateInterfaceValidated(InterfaceType type, const std::string& interfacename, std::istream& sinput, EnvironmentBasePtr penv)
{
    switch(type) {
    case PT_IkSolver: {
        if( interfacename == "ikfast" ) {
            string ikfastname;
            sinput >> ikfastname;
            if( !!sinput ) {
                vector<dReal> vfreeinc((istream_iterator<dReal>(sinput)), istream_iterator<dReal>());
                // look at all the ikfast problem solvers
                IkSolverBasePtr psolver = CreateIkSolverFromName(ikfastname, vfreeinc, penv);
                if( !!psolver ) {
                    return psolver;
                }
            }
        }
        else {
            vector<dReal> vfreeinc((istream_iterator<dReal>(sinput)), istream_iterator<dReal>());
            if( interfacename == "drchubo_v2_leftarm_ikfast" ) {
                return drchubo_v2_leftarm_ikfast::CreateIkSolver(penv, sinput, vfreeinc);
            }
            else if( interfacename == "drchubo_v2_rightarm_ikfast" ) {
                return drchubo_v2_rightarm_ikfast::CreateIkSolver(penv, sinput, vfreeinc);
            }
            else if( interfacename == "drchubo_v2_leftleg_ikfast" ) {
                return drchubo_v2_leftleg_ikfast::CreateIkSolver(penv, sinput, vfreeinc);
            }
            else if( interfacename == "drchubo_v2_rightleg_ikfast" ) {
                return drchubo_v2_rightleg_ikfast::CreateIkSolver(penv, sinput, vfreeinc);
            }
        }
        break;
    }
    case PT_Module:
        if( interfacename == "ikfast") {
            return CreateIkFastModule(penv,sinput);
        }
        break;
    default:
        break;
    }

    return InterfaceBasePtr();
}

void GetPluginAttributesValidated(PLUGININFO& info)
{
    info.interfacenames[PT_IkSolver].push_back("drchubo_v2_leftarm_ikfast");
    info.interfacenames[PT_IkSolver].push_back("drchubo_v2_rightarm_ikfast");
    info.interfacenames[PT_IkSolver].push_back("drchubo_v2_leftleg_ikfast");
    info.interfacenames[PT_IkSolver].push_back("drchubo_v2_rightleg_ikfast");
}

OPENRAVE_PLUGIN_API void DestroyPlugin()
{
    DestroyIkFastLibraries();
}
