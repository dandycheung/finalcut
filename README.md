![FINAL CUT](misc/logo/svg/finalcut-logo.svg)

# Library for creating terminal applications with text-based widgets

FINAL CUT is a powerful and lightweight C++ library for creating [terminal-based applications](https://en.wikipedia.org/wiki/Text-based_user_interface) with numerous text-based widgets. FINAL CUT is designed for simplicity and does not require the functionality of external libraries (such as [ncurses](https://invisible-island.net/ncurses/ncurses.html) or [termbox](https://code.google.com/archive/p/termbox/)) but still offers full [mouse](doc/mouse-control.md#title-bar-actions-on-mouse-clicks) support, Unicode compatibility, and versatile widget functions.

It provides [UTF-8](https://en.wikipedia.org/wiki/UTF-8) character encoding, [full-width character](https://en.wikipedia.org/wiki/Halfwidth_and_fullwidth_forms) support, and the ability to display [combined Unicode characters](https://en.wikipedia.org/wiki/Combining_character). The library helps the developer to create an easy-to-use text console application and allows handling multiple text windows on the screen.

The design of FINAL CUT's C++ class structure was inspired by the Qt framework. It provides a variety of common controls, including dialog boxes, push buttons, check boxes, radio buttons, input lines, list boxes, and status bars.

![Architecture of the sub-systems of a FINAL CUT application](doc/subsystem-architecture.svg)


## Building and Code Analysis

|                    | Badge |
|-------------------:|:------|
| *Latest release*   | [![Latest Release](https://img.shields.io/github/release/gansm/finalcut.svg)](https://github.com/gansm/finalcut/releases) |
| *License*          | [![LGPL v3](https://img.shields.io/badge/License-LGPL_v3-blue.svg)](LICENSE) |
| *Class Reference*  | [![documented](https://codedocs.xyz/gansm/finalcut.svg)](https://codedocs.xyz/gansm/finalcut/hierarchy.html) |
| *ARM build*        | [![ARM build](https://github.com/gansm/finalcut/actions/workflows/arm.yml/badge.svg)](https://github.com/gansm/finalcut/actions/workflows/arm.yml) |
| *FreeBSD build*    | [![FreeBSD build](https://github.com/gansm/finalcut/actions/workflows/freebsd.yml/badge.svg)](https://github.com/gansm/finalcut/actions/workflows/freebsd.yml) |
| *NetBSD build*     | [![NetBSD build](https://github.com/gansm/finalcut/actions/workflows/netbsd.yml/badge.svg)](https://github.com/gansm/finalcut/actions/workflows/netbsd.yml) |
| *OpenBSD build*    | [![OpenBSD build](https://github.com/gansm/finalcut/actions/workflows/openbsd.yml/badge.svg)](https://github.com/gansm/finalcut/actions/workflows/openbsd.yml) |
| *macOS build*      | [![macOS build](https://github.com/gansm/finalcut/actions/workflows/macos.yml/badge.svg)](https://github.com/gansm/finalcut/actions/workflows/macos.yml) |
| *Cygwin build*     | [![Cygwin build](https://github.com/gansm/finalcut/actions/workflows/cygwin.yml/badge.svg)](https://github.com/gansm/finalcut/actions/workflows/cygwin.yml) |
| *Solaris build*    | [![Solaris build](https://github.com/gansm/finalcut/actions/workflows/solaris.yml/badge.svg)](https://github.com/gansm/finalcut/actions/workflows/solaris.yml) |
| *CodeQL analysis*  | [![CodeQL analysis](https://github.com/gansm/finalcut/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/gansm/finalcut/security/code-scanning) |
| *Coverity Scan*    | [![Coverity Scan Status](https://img.shields.io/coverity/scan/6508.svg)](https://scan.coverity.com/projects/6508 ) |
| *SonarCloud*       | [![Quality gate](https://sonarcloud.io/api/project_badges/measure?project=gansm_finalcut&metric=alert_status)](https://sonarcloud.io/dashboard?id=gansm_finalcut) |
| *CodeFactor*       | [![CodeFactor](https://www.codefactor.io/repository/github/gansm/finalcut/badge)](https://www.codefactor.io/repository/github/gansm/finalcut) |
| *SIGRID*       | [![sigrid-publish](https://github.com/gansm/finalcut/actions/workflows/sigrid-publish.yml/badge.svg?branch=main)](https://github.com/gansm/finalcut/actions/workflows/sigrid-publish.yml) |


## Installation

Before installing FINAL CUT, check if your computer meets the requirements. You can find these in the FAQ section under "[What do I need to build this library?](doc/faq.md#what-do-i-need-to-build-this-library)".

```bash
> git clone https://github.com/gansm/finalcut.git
> cd finalcut
> autoreconf --install --force
> ./configure --prefix=/usr
> make
> su -c "make install"
```

## Supported Platforms

FINAL CUT currently works on the following platforms:

* Linux
* FreeBSD
* NetBSD
* OpenBSD
* macOS
* Cygwin
* GNU Hurd
* Solaris

If your platform is not listed here, it may still be compatible with FINAL CUT. [Contributions](Contributing.md) to extend the platform support are welcome!

## Documentation

Read the documentation on the [first steps](doc/first-steps.md#first-steps-with-the-final-cut-widget-toolkit) in FINAL CUT to find out how to use the library.

## Frequently Asked Questions

Check out the FINAL CUT [FAQ](doc/faq.md#frequently-asked-questions) for common questions and answers.

## Screenshots

Explore the power of FINAL CUT with these examples:

![FFileDialog](doc/fileopen-dialog.png)
<br />*FFileDialog widget with incremental search*<br /><br />

![FProgressbar](doc/progress-bar.png)
<br />*FProgressbar widget*<br /><br />

![XPM Viewer](doc/xpmview.png)
<br />*X PixMap (XPM) viewer example*<br /><br />

![FTextView](doc/textview.png)
<br />*Scrollable text in an FTextView widget*<br /><br />

![Mandelbrot set](doc/Mandelbrot.png)
<br />*Mandelbrot set example*<br /><br />

## FINAL CUT newfont

This project contains [NewFont](final/font/), a graphical text font for X11 and the Linux console:

![ui example in newfont mode](doc/newfont1.png)
<br />*UI example in NewFont mode*<br /><br />

![drive symbols](doc/newfont2.png)
<br />*Drive symbols*<br /><br />

![calculator](doc/calculator.png)
<br />*Calculator example in NewFont mode*<br /><br />

## Benchmark

Measure the [terminal character output speed](doc/benchmark.md#benchmark) with the Rotozoomer example.

## Virtual Terminal

FINAL CUT uses a virtual terminal to print character via an update method on the screen. It provides (as an overlying layer) virtual windows for the realization of window movements. The update methods only transfer differences to the virtual terminal or physical screen.

<pre style="line-height: 1 !important;">
 print(...)
printf(...)
  │
  │          ╔════════════════════════[ vterm ]════════════════════════╗
  │          ║createVTerm()                                            ║
  │          ║                                   ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐ ║
  │          ║                                                         ║
  │          ║                                   │ restoreVTerm(box) │ ║
  │  ┌───────╨────[ vwin ]────────────┐                                ║
  │  │createArea(size)                │          └ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┘ ║
  │  │                                │                                ║
  │  │                                │                                ║
  └──┼────────►                putArea(pos,area) ────►                 ║
     │                                │                                ║
     │                   ◄──── getArea(pos,area)                       ║
     │                                │                                ║
     │                                │                                ║
     │                                │                                ║
     │          resizeArea(size, area)│                                ║
     └───────╥────────────────────────┘                                ║
             ║                                                         ║
             ║       │                                resizeVTerm(size)║
             ╚═══════▼═════════════════════════════════════════════════╝
                     │
                     │   putVTerm()
                     └──────────────────► updateTerminalLine(y)
                       updateTerminal()            │
                                                   ▼
                                           ┌───────────────┐
                                           │ output_buffer │
                                           └───────────────┘
                                                   │
                                                   │ flush()
                                                   │
                                                   ▼
                                           ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
                                           ▌               ▐
                                           ▌    screen     ▐
                                           ▌ ───────────── ▐
                                           ▌ real terminal ▐
                                           ▌               ▐
                                           ▀▀▀▀▀▀▀███▀▀▀▀▀▀▀
                                                  ███
                                               ▀▀▀▀▀▀▀▀▀
</pre>

## Class Digramm

<pre style="line-height: 1 !important;">
    ┌────────────┐1
    │ FTermLinux ├------┐
    └────────────┘      :
  ┌──────────────┐1     :
  │ FTermFreeBSD ├------┐
  └──────────────┘      :
  ┌──────────────┐1     :
  │ FTermOpenBSD ├------┐
  └──────────────┘      :
┌────────────────┐1     :
│ FTermDetection ├------┐
└────────────────┘      :
┌────────────────┐1     :
│ FTermcapQuirks ├------┐
└────────────────┘      :            ┌───────────┐
┌────────────────┐1     :       ┌────┤ FKeyEvent │
│ FTermXTerminal ├------┐       │    └───────────┘
└────────────────┘      :       │    ┌─────────────┐
      ┌──────────┐1     :       ├────┤ FMouseEvent │
      │ FTermcap ├------┐       │    └─────────────┘
      └──────────┘      :       │    ┌─────────────┐
      ┌──────────┐1     :       ├────┤ FWheelEvent │
      │ FTermios ├------┐       │    └─────────────┘
      └──────────┘      :       │    ┌─────────────┐
 ┌───────────────┐1     :       ├────┤ FFocusEvent │
 │ FColorPalette ├------┐       │    └─────────────┘
 └───────────────┘      :       │    ┌─────────────┐
     ┌───────────┐1     :       ├────┤ FAccelEvent │
     │ FOptiMove ├------┐       │    └─────────────┘
     └───────────┘      :       │    ┌──────────────┐
     ┌───────────┐1     :       ├────┤ FResizeEvent │
     │ FOptiAttr ├------┐       │    └──────────────┘
     └───────────┘      :       │    ┌────────────┐
     ┌───────────┐1     :       ├────┤ FShowEvent │
     │ FKeyboard ├------┐       │    └────────────┘
     └───────────┘      :       │    ┌────────────┐
 ┌───────────────┐1     :       ├────┤ FHideEvent │
 │ FMouseControl ├------┐       │    └────────────┘
 └───────────────┘      :       │    ┌─────────────┐
       ┌─────────┐1     :       ├────┤ FCloseEvent │
       │ FSystem ├------┐       │    └─────────────┘
       └─────────┘      :       │    ┌─────────────┐
       ┌─────────┐*     :       ├────┤ FTimerEvent │
       │ FString ├---┐  :       │    └─────────────┘
       └─────────┘   :  :       │    ┌────────────┐1    1┌───────┐
 ┌───────────────┐*  :  :       ├────┤ FUserEvent ├------┤ FData │
 │ FStringStream ├---┐  :       │    └────────────┘      └───────┘
 └───────────────┘   :  :       │        ┌──────┐   ┌─────────┐
        ┌────────┐*  :  :       │        │ FLog │◄──┤ FLogger │
        │ FPoint ├---┐  :       │        └──┬───┘   └─────────┘
        └────────┘   :  :       │           :1
         ┌───────┐*  :  :       │        ┌──┴───────────┐
         │ FRect ├---┐  :       │   ┌────┤ FApplication │
         └───────┘   :  :       │   │    └──────────────┘
         ┌───────┐*  :  :       │   │    ┌────────┐
         │ FSize ├---┐  :       │   ├────┤ FLabel │
         └───────┘   :  :       │   │    └────────┘
                     :1 :1      │   │    ┌───────────┐
                 ┌───┴──┴┐      │   ├────┤ FLineEdit │
                 │ FTerm │      │   │    └───────────┘
                 └───┬───┘      │   │    ┌──────────┐
                     :1         │   ├────┤ FSpinBox │
┌─────────┐   ┌──────┴──────┐   │   │    └──────────┘
│ FOutput │◄──┤ FTermOutput │   │   │    ┌─────────┐
└────┬────┘   └─────────────┘   │   ├────┤ FButton │
     :             ┌────────┐   │   │    └─────────┘
     :1            │ FEvent │◄──┘   │    ┌──────────────┐      ┌──────────────┐
 ┌───┴────┐        └────┬───┘       ├────┤ FButtonGroup │   ┌──┤ FRadioButton │
 │ FVTerm │◄──┐         :1          │    └──────────────┘   │  └──────────────┘
 └────────┘   │    ┌────┴────┐      │    ┌───────────────┐  │  ┌───────────┐
              ├────┤ FWidget │◄─────┼────┤ FToggleButton │◄─┼──┤ FCheckBox │
┌─────────┐   │    └────┬────┘      │    └───────────────┘  │  └───────────┘
│ FObject │◄──┘         :1          │    ┌──────────────┐   │  ┌─────────┐
└────┬────┘      ┌──────┴────────┐  ├────┤ FProgressbar │   └──┤ FSwitch │
     ▼           │ FWidgetColors │  │    └──────────────┘      └─────────┘
 ┌───┴────┐      └───────────────┘  │    ┌────────────┐
 │ FTimer │                         ├────┤ FScrollbar │
 └────────┘                         │    └────────────┘
                                    │    ┌───────────┐
                                    ├────┤ FTextView │
                                    │    └───────────┘
                                    │    ┌───────────┐1    1┌──────────────────┐
                                    ├────┤ FComboBox ├------┤ FDropDownListBox │
                                    │    └───────────┘      └──────────────────┘
 ┌──────────────┐1                  │    ┌──────────┐1     *┌──────────────┐1
 │ FVTermBuffer ├-------------------├────┤ FListBox ├-------┤ FListBoxItem ├--┐
 └──────────────┘                   │    └──────────┘       └──────────────┘  :
                                    │   1┌───────────┐1    *┌───────────────┐ :
                                    ├────┤ FListView ├------┤ FListViewItem │ :
                                    │    └───────────┘      └────────┬──────┘ :
                                    │    ┌─────────────┐             :1       :
                                    ├────┤ FScrollView │         ┌───┴───┐1   :
                                    │    └─────────────┘         │ FData ├----┘
                                    │                            └───────┘
                                    │    ┌────────────┐1   *┌────────────┐
                                    │ ┌──┤ FStatusBar ├-----┤ FStatusKey │
                                    │ │  └────────────┘     └────────────┘
                                    │ │
                                    │ ▼                       ┌─────────────┐
                                ┌───┴─┴───┐  ┌─────────┐   ┌──┤ FFileDialog │
                                │ FWindow │◄─┤ FDialog │◄──┤  └─────────────┘
                                └──┬──┬───┘  └─────────┘   │  ┌─────────────┐
                                   ▲  ▲                    └──┤ FMessageBox │
                                   │  │                       └─────────────┘
                                   │  │      ┌──────────┐  ┌────────────────┐
                                   │  └──────┤ FToolTip │◄─┤ FBusyIndicator │
                                   │         └──────────┘  └────────────────┘
                                   └───────────────┐          ┌──────────┐
                                                   │      ┌───┤ FMenuBar │
                                  ┌───────────┐    └──────┤   └──────────┘
                                  │ FMenuList │◄──────────┤   ┌───────┐
                                  └────┬──────┘           └───┤ FMenu │◄──┐
                                       :1                     └───────┘   │
                                       :            ┌─────────────────┐   │
                                       :            │ FDialogListMenu ├───┘
                                       :            └─────────────────┘
                                       └--------------------------------┐
                                       :*          ┌────────────────┐*  :
                                  ┌────┴─────┐  ┌──┤ FCheckMenuItem ├---┘
                                  │FMenuItem │◄─┤  └────────────────┘   :
                                  └──────────┘  │  ┌────────────────┐*  :
                                                └──┤ FRadioMenuItem ├---┘
                                                   └────────────────┘
</pre>

## Contributing and reporting bugs

We encourage community involvement in improving FINAL CUT. If you find bugs or [issues](https://github.com/gansm/finalcut/issues), report them here. For contributions, please review our [Contributing Guidelines](Contributing.md).

## License

FINAL CUT is licensed under the GNU Lesser General Public License v3.0. See the [LGPL v3.0 license page](https://www.gnu.org/licenses/lgpl-3.0-standalone.html) for more details. <a href="https://www.gnu.org/licenses/lgpl-3.0-standalone.html"><img width="200" align="right" src="https://upload.wikimedia.org/wikipedia/commons/3/3b/LGPLv3_Logo.svg" alt="LGPLv3" data-canonical-src="https://upload.wikimedia.org/wikipedia/commons/3/3b/LGPLv3_Logo.svg"></a>
