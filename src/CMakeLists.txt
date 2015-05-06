set(LIB_TARGET lass)

find_package (Cat)
if (CAT_FOUND)
  include_directories(${CAT_INCLUDE_DIR})
  set(LIBS ${LIBS} ${CAT_LIBRARIES})
endif (CAT_FOUND)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
include_directories(${SRC_DIR})

set(HEADERS

"${SRC_DIR}/lass.h"

)

set(CGSOLVER_DIR "${SRC_DIR}/cgsolver")
include_directories(${CGSOLVER_DIR})

set(CGSOLVER_HEADERS

"${CGSOLVER_DIR}/cgsolver.h"
"${CGSOLVER_DIR}/cgsolver_matrix.h"
"${CGSOLVER_DIR}/cgsolver_new.h"
"${CGSOLVER_DIR}/cgsolver_old.h"

)

set(CGSOLVER_SOURCES

"${CGSOLVER_DIR}/cgsolver.C"

)

set(SOURCES ${SOURCES} ${CGSOLVER_SOURCES})

set(VZDEIGEN_DIR "${SRC_DIR}/vzdeigen")
set(VZDEIGEN_YUIO "${CMAKE_SOURCE_DIR}/external/yuio.f")

if(EXISTS ${VZDEIGEN_YUIO})

	include_directories(${VZDEIGEN_DIR})

	set(VZDEIGEN_HEADERS

	"${VZDEIGEN_DIR}/vzdeigen.h"

	)

	set(VZDEIGEN_SOURCES

	"${VZDEIGEN_DIR}/vzdeigen.f"
	"${VZDEIGEN_YUIO}"

	)

	set(SOURCES ${SOURCES} ${VZDEIGEN_SOURCES})

endif()

add_library(${LIB_TARGET} SHARED ${SOURCES})
target_include_directories(${LIB_TARGET}
  PUBLIC
    # Headers used from source/build location:
    "$<BUILD_INTERFACE:${SRC_DIR}>"
    # Headers used from installed location:
    "$<INSTALL_INTERFACE:include/lass>"     
)
target_link_libraries(${LIB_TARGET} ${LIBS})

install (TARGETS ${LIB_TARGET} DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include/${LIB_TARGET})
install (FILES ${CGSOLVER_HEADERS} DESTINATION include/${LIB_TARGET}/cgsolver)

if(EXISTS ${VZDEIGEN_YUIO})

	install (FILES ${VZDEIGEN_HEADERS} DESTINATION include/${LIB_TARGET}/vzdeigen)

endif()

