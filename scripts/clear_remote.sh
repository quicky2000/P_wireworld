#!/bin/sh -f
git remote remove EXT_systemc_remote
git remote remove EXT_xmlParser_remote
git remote remove lib_bmp_remote
git remote remove parameter_manager_remote
git remote remove quicky_exception_remote
git remote remove quicky_tools_remote
git remote remove quicky_utils_remote
git remote remove simple_gui_remote
git remote remove wireworld_remote
git remote remove wireworld_common_remote
git remote remove wireworld_computer_remote
git remote remove wireworld_systemc_remote
git remote remove wireworld_tool_remote
git branch -D EXT_systemc_branch
git branch -D EXT_xmlParser_branch
git branch -D lib_bmp_branch
git branch -D parameter_manager_branch
git branch -D quicky_exception_branch
git branch -D quicky_tools_branch
git branch -D quicky_utils_branch
git branch -D simple_gui_branch
git branch -D wireworld_branch
git branch -D wireworld_common_branch
git branch -D wireworld_computer_branch
git branch -D wireworld_systemc_branch
git branch -D wireworld_tool_branch
#EOF
