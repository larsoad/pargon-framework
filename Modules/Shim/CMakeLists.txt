set(INCLUDES
	Pargon/Shim.h
)

set(SOURCES
)

set(LIBRARIES
	fmt::fmt
	nanorange
	scn::scn
	span
)

add_pargon_dependency(fmtlib)
add_pargon_dependency(nanorange)
add_pargon_dependency(scnlib)
add_pargon_dependency(span)
add_pargon_module(PargonShim "${INCLUDES}" "${SOURCES}" "${LIBRARIES}" "")
