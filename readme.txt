#######################################################################
#
# Win32::Clipboard - Perl module to interact with the Windows Clipboard
# ^^^^^^^^^^^^^^^^
#
# Version: 0.03 (23 Apr 1997)
# by Aldo Calpini <dada@divinf.it>
#
#######################################################################


Manifest
^^^^^^^^
The file Win32Clipboard-0.03.zip contains:

    README
    README.TXT
    INSTALL.BAT
    TEST.PL
    CLIPBOARD.PM
    CLIPBOARD.PLL.110
    CLIPBOARD.PLL.30X
    SOURCE/README.TXT
    SOURCE/CLIPBOARD.CPP
    SOURCE/CLIPBOARD.DEF
    SOURCE/CLIPBOARD.MAK
    SOURCE/CLIPBOARD300.MAK

(be sure to have unzipped it with LONG FILE NAMES and PATHS)

Installation
^^^^^^^^^^^^
    1. Run the INSTALL.BAT program.
    2. Run the TEST.PL script to see if everything works.
    3. Have fun.


What's new in this version
^^^^^^^^^^^^^^^^^^^^^^^^^^
Changes from version 0.01 are:
    . The PLL file now comes in 2 versions, one for Perl version 5.001 (build 110)
      and one for Perl version 5.003 (build 300 and higher, EXCEPT 304).
    . Added an installation program which will automatically copy the right files
      in the right place.
    . Added an object-oriented programming approach.

Usage
^^^^^
Put this line at the beginning of your Perl scripts:

    use Win32::Clipboard;

And then play with the following functions (I believe they are 
self-explanatory):

    $text = Win32::Clipboard::Get();
    Win32::Clipboard::Set("blah blah blah");
    Win32::Clipboard::Empty();

Alternatively, you can use the clipboard as an object with this syntax:

    $Clip = Win32::Clipboard();
    $text = $Clip->Get();
    $Clip->Set("blah blah blah");
    $Clip->Empty();

Note that creating the object with a parameter automatically sets
the clipboard content to that value:

    $Clip = Win32::Clipboard("blah blah blah");


On-line
^^^^^^^
You can always find the latest version of this package online at:

    http://www.divinf.it/dada/perl/clipboard

Send any comment to:

    Aldo Calpini  <dada@divinf.it>

