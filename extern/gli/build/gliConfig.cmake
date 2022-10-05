set(GLI_VERSION "0.8.3")
set(GLI_INCLUDE_DIRS "D:/local/my_github_repos/QtProjectTestsVS2022/jcqt3DTest/extern/gli/src/gli")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
	include("${CMAKE_CURRENT_LIST_DIR}/gliTargets.cmake")
endif()
