13.7.2014


We currently have:

* the complete dalvik vm (all dependencies it has from android ported to vanilla linux)
* pixelflinger
* properties server
* complete documentation on the build system and how to make that go



10.7.

(6:32:00 PM) ingwa2_: What to expect from the updates would be a more or less complete dalvik bytecode interpreter.
(6:32:22 PM) ingwa2_: There are 9 parts of it, of which 2 are building in the current checked-in sources. 



11.7.

Currently the entire dalvik system builds including the tools. What we are 
left with is a complete system with headers, libraries and binaries installed 
to the host system. 

Left to merge is the settings kded5 plugin and building the java-based tools. 
This will be in by tomorrow.

Some notes to help understand progress a bit:

* some of the commits represent multiple experiments at doing it in different 
ways. two examples of this are:

        * the bionic-included memory allocator. i tried including the files from 
bionic directly into the vm library by adding them to the dalvik repository. 
this worked, but as bionic is also moving around my concern is this would lead 
to de-synchronization between our build and the bugfixes and performance 
improvements that go into bionic. so then i did an out-of-tree build that 
depends on bionic (which is what it does now, in fact). there were two 
variants on that as well: one where the configuration of the allocator was done 
in the CMake build system and one where the configuration was done in the 
dalvik VM's DlMalloc.cpp file directly. the last is the variant chosen

        * assembler. this was pretty annoying as there were three options: a) 
generate assembler from the stubs myself and patch that into the build; b) use 
the pre-included assembler files with modifications where needed; c) use the 
generic C implementation. i actually went with the latter until i realized 
after futzing with it that this was not going to be any easier that pulling in 
the assembler directly. so then i had to figure out how, in the Android 
environment, the assembler for a given platform is actually pulled in (which 
is when i realized there was both an (a) and a (b) option ... *sigh*), and 
eventually settled on c.

As the documentation is almost always the code itself, some of these decisions 
took brute-force experimentation and reading through the sources while 
consulting mailing list archives for hints and ideas.




15.5.


I have the dalvik stack building and have been working on the runtime bits 
that the applications running on top of dalvik assume are there. Some of these 
components were actually implemented in the Linux kernel itself for what seems 
to be two reasons:

* performance on very limited hardware
* security (you can more easily guarantee certain things when running in the 
kernel)

It isn't realistic to expect people to patch their kernel to become more 
Android like, if that is even possible (which it wouldn't be in many 
situations .. patches would be kernel version specific, etc) so I've been 
pushing forward with the userspace replacements as planned. Fortunately dalvik 
itself has hooks to run inside an emulated environment so Android app devs can 
work on "real" operating systems and hardware to write their apps and then 
deploy for testing once the application basically works. I'm taking advantage 
of those hooks as they are exactly what we need :)



25.4.


== Planning and research

I identified which repositories will require patches that we carry downstream and got that number down to just three. While this took some time to complete, it has allowed me to work straight ahead since without interruptions or surprises.


== Build System

The out-of-tree buildsystem approach is working very well. It has gone through 
a few revisions, and there are still some "cleanliness" things I'd like 
undertake over time, but for now it is allowing me to cherry pick the parts we 
need for Dalvik and port only what is absolutely required (right down to the 
file level: some libraries are currently built without some API they would have 
on Android). 

I'm keeping the documentation up to date on how to build things, and that will 
expand again in detail as I get closer to finished (no point in documenting 
things that are still moving around).


== Build progress

All the pieces outside of Dalvik are now building as required and I am 
currently working on the core Dalvik virtual machine. It nearly compiles 
already, in fact. The last bits are some things it relies on from bionic 
(Android's libc) which I started porting over yesterday. (Bionic is not an 
acceptable dependency as it replaces libc!) This will be finished on Monday and 
then the vm should build and link successfully.

The remainder of the pieces in the dalvik repository should follow quickly as 
they are tiny (mostly helpers and dev tools) which means that before the end 
of this month I will have reached the first milestone, as intended: produce a 
Dalvik that builds on vanilla Linux on x86.


== Next month

Next month's [May] work is to produce the necessary runtime components. That 
includes:

* build of the java components
* write a properties server (this is provided by the android kernel and is 
entirely non-standard, but a user-space server is supported if it is built 
with the right options, which is what the build system currently does)
* write a launch service (this is a long-running daemon that bootstraps the vm 
and then launches apk's on request)
* use the above to get an apk running!

The two daemons will end up in the shashlik repository in a tier3 build 
directory (next to tier1 and tier2 which are used to build the Dalvik runtime)

I'm not 100% sure how much work the above will be, though I know it will fit 
within the next month's hours. I might have time next month to already start 
on the Plasma integration, but I can't yet promise that.





23.4.

Just another quick update: all the legwork I did up until now is finally paying 
off. I'm already into building dalvik itself. There was more porting work than 
I hoped (lots of things assumed components from android, like their custom 
libc (bionic) in subtle ways), but I'm getting there and have broken through a 
few important barriers and am on to parts of the dalvik runtime itself.






18.4.
lots of initial work to get to the starting point. 

I have not synced anything to the git repo because I will actually need at 
least 3 more repos, possibly more. These will include:

* android-core
* android-libcore
* dalvik

They all need (and are getting) patches, and the only sane way to track 
upstream and keep those patches maintainable is to clone each of the 
repositories individually.

There are two other hard dependencies which I may be able to avoid changing or 
even requiring after all the patching is in place:

* libnativehelper
* safe-iop

The shashlik repository will still be needed, though: I am putting the build 
system in the shashlik git repo. This will give us a "meta build" that lives 
in the shashlik repo that will build all the necessary pieces of the above 
mentioned repositories. This keeps all those files out of the cloned repos, 
which means the cloned repos will *only* have the needed patches, but no new 
files due to the build system. .. it should be much easier to track changes 
over time that way.

So the shashlik repo will end up with documentation and a set of build files 
which will require the other repos above checked out to actually build 
everything. (Perhaps more repos .. but currently I am managing to keep other 
depedencies out .. there is a LOT of old and odd cruft in these repositories, 
things from the early days of android and even things for hardware platforms 
and operating systems we do not need to support)






9.4.2014

Making  pretty great progress at the moment on shashlik. I've been documenting 
the dependcies of dalvik which has sent me through the bowels of the android 
base system, but severing what bits of hard-coded ties are at that level seem 
pretty straight forward at this point.

Some useful decision points have come and gone now, including which version of 
dalvik to focus on: the version that comes with kitkat. I don't want to be 
chasing their development in master, so will instead be working on their 
kitkat branch.


The roadmap / gameplan is:

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


1.4.2014

Shashlik Project started
