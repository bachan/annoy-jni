Somehow it seems that annoy-jni from maven repo crashes on huge ann files with custom metrics (i.e. Euclidean) and I can't find C++ JNI bindings source code to track down the reason, so I had to recreate these bindings quickly for my own use.

Sources of `annoylib.h` and `kissrandom.h` are just stored in this repo, because I'm lazy to set up a proper dependency process.
