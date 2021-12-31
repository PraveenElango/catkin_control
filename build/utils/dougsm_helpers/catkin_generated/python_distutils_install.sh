#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/crslab/catkin_control/src/utils/dougsm_helpers"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/crslab/catkin_control/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/crslab/catkin_control/install/lib/python2.7/dist-packages:/home/crslab/catkin_control/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/crslab/catkin_control/build" \
    "/usr/bin/python2" \
    "/home/crslab/catkin_control/src/utils/dougsm_helpers/setup.py" \
     \
    build --build-base "/home/crslab/catkin_control/build/utils/dougsm_helpers" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/crslab/catkin_control/install" --install-scripts="/home/crslab/catkin_control/install/bin"
