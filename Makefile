SRCDIR?=.
BUILDDIR?=build
BUILDTYPE?=RelWithDebInfo

configure:
	cmake \
		-B${BUILDDIR} \
		-H${SRCDIR} \
		-DCMAKE_BUILD_TYPE=${BUILDTYPE} \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DENABLE_TESTS=ON \

.PHONY: configure
.SILENT: configure

build: configure
	cmake --build ${BUILDDIR};
.PHONY: build
.SILENT: build

clean:
	rm -rf ${BUILDDIR}
.PHONY: clean
.SILENT: clean

rebuild: | clean build
.PHONY: rebuild

test: build
	cmake --build ${BUILDDIR} --target test
.PHONY: test
.SILENT: test
