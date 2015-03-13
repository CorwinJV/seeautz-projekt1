# SVN & You! #

In order to download a copy of the live code-base, you should use a program called Subversion. This program, also known as SVN, is a version control program, which can allow us to make sure our code-base is kept safe.

# Finding the right SVN Client #
There are two good ways of getting onto SVN on a windows machine. The first (and harder) method is to download [Cygwin](http://www.cygwin.com/). When installing Cygwin, make sure to scroll down the list of additional programs to install and check Subversion client.

## Cygwin & SVN ##
After installing, Cygwin should have placed a shortcut on your desktop. You can double click that and enter the Cygwin shell. Cygwin is basically a Linux emulator for certain apps.. sort of.. kind of. Hard to explain but it allows us to use SVN.

Now you should navigate to a place you'd like to house your code. For instance, make a new folder at C:/MyProjects/ and navigate there. I'll show you the commands to do this.

cd C:/
mkdir MyProjects

Now click on the source tab of our google code projekt and type the member's-access command in your Cygwin window. There's a link there to find your password.

That should automatically suck everything down to your hard-drive. When using SVN, there are only a few commands you'll ever need to type:

This pulls down any new or modified files from the repository.
> svn update
This commits a file (or all changed files) to the repository, effectively replacing the current build. The filename part is optional but the comment is not (explain what you're doing and why a little bit).
> svn commit {filename} -m "Your Comment Goes Here"
SVN Status shows you what state the files are currently in (modified? conflicted? added?).
> svn status
SVN add well, it adds files to the repository. Don't forget you can't just add the files, you have to add them and then commit them to the repository.
> svn add {filename}


You can cd (change directory) and ls (list) the contents of every folder. You can also mv (move) files, and rm (remove) them. Good luck! Command line (kind of cool.)

## TortoiseSVN ##
Download [TortoiseSVN](http://tortoisesvn.tigris.org/) here, and install it. After the installation, you should move to a new directory (as above) such as C:/MyProjects/. Here, right click in the window, and go down to SVN Checkout..
There you can input all of the same info shown above.

After it checks out all of the files it should be obvious that you have a now living copy of the code-base. Have fun with it and try not to make any build-breaking checkins :)!