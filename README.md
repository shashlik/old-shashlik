shashlik
========

Android Simulated Environment

The roadmap / plan is:

* Enumerate components and dependencies

There are 9 items on this list, and I've worked through the first two. Working 
my way up the stack should become easier as lower level items that are already 
ready will be re-used, so each successive entry should have less and less work 
involved.


* Build components

After enumerating a component set, I will move to this stage; once the 
component set builds, I will return to "Enumerate components and dependencies" 
to work on the next entry.

This is where source code actually starts getting modified, and at this point I 
will import a fork of the relevant code base into a new git repository and 
start working on it there. It will be regularly rebased on the upstream repos 
to keep up with changes there. 

I have decided to start out by moving the build system to cmake. The reason 
for this is multiple:

- The Android build system is based on the old autotools stuff which is just 
horrible
- It means not having to touch their build system, so changes in it won't 
affect us
- As new files appear in the repositories over time, it will be evident what 
needs review (and porting if needed) as it will be missing from the cmake 
build system
- It will be much much simpler to maintain in the long run

The builds are all quite simple looking. For the base "libdex" library in 
dalvik, which is the first item in the components list, it looks like I'll have 
to come up with just 5 cmake files, each of which makes a single library .. 
which is child's play :)

Getting things to actually build and link will be a bit more work. There are 
areas where they assume they are running on an android system, for instance, 
and that will need some reimplementation of functions to work on a regular 
Linux system. Thought, to be  honest, it's not as bad as I feared it might be.

The code quality is not awesome in many places, but  we already knew that 
about Android :/


* Implement system integration points

During the first stage enumeration I am also documenting system integration 
points I find. To get things building, things will mostly just get stubbed in. 
Once the libraries and necessary binaries are all building, I will work on 
implementing the useful system integration points. Some system integration 
points are simply not interesting, however (such as the hooks used to do 
system startup).

Some hooks will be crucial, however, such as the hooks into surfaceflinger to 
get openGL surfaces for the apps to render into, and those will take the bulk 
of the effort I think.

There will also likely be areas like the handling of the "back" and "home" 
software keys which apps expect to work a specific way under Android. This list 
will grow and shrink as I move stepwise through the first two phases. above


* Create launch daemon

The way Dalvik works (or .. is expected to work anyways ..) is that there is a 
long-running instance of the VM that is used as a launcher. When an app 
starts, this launcher forks itself into another process (which Dalvik 
apparently is optimized for...) and starts the app. The launcher then manages 
the apps as needed.


* Test against real world apps

Once there is a launch daemon, then we can start testing against real world 
apps. I expect this to reveal what remaining system integration work needs to 
be done on a practical level.


* Plasma workspace integration

Once things are running somewhat usefully, integration with Plasma will come 
next. That includes form factor awareness, taskbar integration, application 
launcher integration, windowed modes, etc. Some of these things will be a bit 
"funny" for the Android apps as not all the concepts used on the various form 
factors Plasma supports map to the Android concept. This is why Google does 
not use Android for their Chrome Books, for instance. In any case, I've 
compiled a short list of targets for this as well.
