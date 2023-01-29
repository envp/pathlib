SRCDIR?=.
BUILDDIR?=build
BUILDTYPE?=RelWithDebInfo

configure:
	cmake \
		-DCMAKE_BUILD_TYPE=${BUILDTYPE} \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DPATHLIB_BUILD_EXAMPLES=ON \
		-B${BUILDDIR} \
		-H${SRCDIR}
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

install: build
	cmake --build ${BUILDDIR} --target install
.PHONY: install
.SILENT: install

test: build
	cmake --build ${BUILDDIR} --target test
.PHONY: test
.SILENT: test
