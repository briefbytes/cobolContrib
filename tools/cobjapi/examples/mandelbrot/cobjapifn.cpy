*>******************************************************************************
*>  This file is part of cobjapi.
*>
*>  cobjapifn.cpy is free software: you can redistribute it and/or 
*>  modify it under the terms of the GNU Lesser General Public License as 
*>  published by the Free Software Foundation, either version 3 of the License,
*>  or (at your option) any later version.
*>
*>  cobjapifn.cpy is distributed in the hope that it will be useful, 
*>  but WITHOUT ANY WARRANTY; without even the implied warranty of 
*>  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*>  See the GNU Lesser General Public License for more details.
*>
*>  You should have received a copy of the GNU Lesser General Public License 
*>  along with cobjapifn.cpy.
*>  If not, see <http://www.gnu.org/licenses/>.
*>******************************************************************************

*>******************************************************************************
*> Program:      cobjapifn.cpy
*>
*> Purpose:      Functions for the cobjapi wrapper
*>
*> Author:       Laszlo Erdos - https://www.facebook.com/wortfee
*>
*> Date-Written: 2014.12.24
*>
*> Tectonics:    ---
*>
*> Usage:        Use this copy file in GnuCOBOL GUI programs, 
*>               in the CONFIGURATION SECTION.
*>
*>******************************************************************************
*> Date       Name / Change description 
*> ========== ==================================================================
*> 2003.02.26 This comment is only for History. The latest Version (V1.0.6) of 
*>            JAPI was released on 02/26/2003. Homepage: http://www.japi.de 
*>------------------------------------------------------------------------------
*> 2014.12.24 Laszlo Erdos: 
*>            - GnuCOBOL support for JAPI added. 
*>******************************************************************************

 FUNCTION J-START
 FUNCTION J-CONNECT
 FUNCTION J-SETPORT
 FUNCTION J-SETDEBUG
 FUNCTION J-FRAME
 FUNCTION J-BUTTON
 FUNCTION J-GRAPHICBUTTON
 FUNCTION J-CHECKBOX
 FUNCTION J-LABEL
 FUNCTION J-GRAPHICLABEL
 FUNCTION J-CANVAS
 FUNCTION J-PANEL
 FUNCTION J-BORDERPANEL
 FUNCTION J-RADIOGROUP
 FUNCTION J-RADIOBUTTON
 FUNCTION J-LIST
 FUNCTION J-CHOICE
 FUNCTION J-DIALOG
 FUNCTION J-WINDOW
 FUNCTION J-POPUPMENU
 FUNCTION J-SCROLLPANE
 FUNCTION J-HSCROLLBAR
 FUNCTION J-VSCROLLBAR
 FUNCTION J-LINE
 FUNCTION J-PRINTER
 FUNCTION J-IMAGE
 FUNCTION J-FILEDIALOG
 FUNCTION J-FILESELECT
 FUNCTION J-MESSAGEBOX
 FUNCTION J-ALERTBOX
 FUNCTION J-CHOICEBOX2
 FUNCTION J-CHOICEBOX3
 FUNCTION J-PROGRESSBAR
 FUNCTION J-LED
 FUNCTION J-SEVENSEGMENT
 FUNCTION J-METER
 FUNCTION J-ADDITEM
 FUNCTION J-TEXTFIELD
 FUNCTION J-TEXTAREA
 FUNCTION J-MENUBAR
 FUNCTION J-MENU
 FUNCTION J-HELPMENU
 FUNCTION J-MENUITEM
 FUNCTION J-CHECKMENUITEM
 FUNCTION J-PACK
 FUNCTION J-PRINT
 FUNCTION J-PLAYSOUNDFILE
 FUNCTION J-PLAY
 FUNCTION J-SOUND
 FUNCTION J-SETFONT
 FUNCTION J-SETFONTNAME
 FUNCTION J-SETFONTSIZE
 FUNCTION J-SETFONTSTYLE
 FUNCTION J-SEPERATOR
 FUNCTION J-DISABLE
 FUNCTION J-ENABLE
 FUNCTION J-GETSTATE
 FUNCTION J-GETROWS
 FUNCTION J-GETCOLUMNS
 FUNCTION J-GETSELECT
 FUNCTION J-ISSELECT
 FUNCTION J-ISVISIBLE
 FUNCTION J-ISPARENT
 FUNCTION J-ISRESIZABLE
 FUNCTION J-SELECT
 FUNCTION J-DESELECT
 FUNCTION J-MULTIPLEMODE
 FUNCTION J-INSERT
 FUNCTION J-REMOVE
 FUNCTION J-REMOVEITEM
 FUNCTION J-REMOVEALL
 FUNCTION J-SETSTATE
 FUNCTION J-SETROWS
 FUNCTION J-SETCOLUMNS
 FUNCTION J-SETICON
 FUNCTION J-SETIMAGE
 FUNCTION J-SETVALUE
 FUNCTION J-SETRADIOGROUP
 FUNCTION J-SETUNITINC
 FUNCTION J-SETBLOCKINC
 FUNCTION J-SETMIN
 FUNCTION J-SETMAX
 FUNCTION J-SETDANGER
 FUNCTION J-SETSLIDESIZE
 FUNCTION J-SETCURSOR
 FUNCTION J-SETRESIZABLE
 FUNCTION J-GETLENGTH
 FUNCTION J-GETVALUE
 FUNCTION J-GETDANGER
 FUNCTION J-GETSCREENHEIGHT
 FUNCTION J-GETSCREENWIDTH
 FUNCTION J-GETHEIGHT
 FUNCTION J-GETWIDTH
 FUNCTION J-GETINSETS
 FUNCTION J-GETLAYOUTID
 FUNCTION J-GETINHEIGHT
 FUNCTION J-GETINWIDTH
 FUNCTION J-GETTEXT
 FUNCTION J-GETITEM
 FUNCTION J-GETITEMCOUNT
 FUNCTION J-DELETE
 FUNCTION J-REPLACETEXT
 FUNCTION J-APPENDTEXT
 FUNCTION J-INSERTTEXT
 FUNCTION J-SETTEXT
 FUNCTION J-SELECTALL
 FUNCTION J-SELECTTEXT
 FUNCTION J-GETSELSTART
 FUNCTION J-GETSELEND
 FUNCTION J-GETSELTEXT
 FUNCTION J-GETCURPOS
 FUNCTION J-SETCURPOS
 FUNCTION J-SETECHOCHAR
 FUNCTION J-SETEDITABLE
 FUNCTION J-SETSHORTCUT
 FUNCTION J-QUIT
 FUNCTION J-KILL
 FUNCTION J-SETSIZE
 FUNCTION J-GETACTION
 FUNCTION J-NEXTACTION
 FUNCTION J-SHOW
 FUNCTION J-SHOWPOPUP
 FUNCTION J-ADD
 FUNCTION J-RELEASE
 FUNCTION J-RELEASEALL
 FUNCTION J-HIDE
 FUNCTION J-DISPOSE
 FUNCTION J-SETPOS
 FUNCTION J-GETVIEWPORTHEIGHT
 FUNCTION J-GETVIEWPORTWIDTH
 FUNCTION J-GETXPOS
 FUNCTION J-GETYPOS
 FUNCTION J-GETPOS
 FUNCTION J-GETPARENTID
 FUNCTION J-SETFOCUS
 FUNCTION J-HASFOCUS
 FUNCTION J-GETSTRINGWIDTH
 FUNCTION J-GETFONTHEIGHT
 FUNCTION J-GETFONTASCENT
 FUNCTION J-KEYLISTENER
 FUNCTION J-GETKEYCODE
 FUNCTION J-GETKEYCHAR
 FUNCTION J-MOUSELISTENER
 FUNCTION J-GETMOUSEX
 FUNCTION J-GETMOUSEY
 FUNCTION J-GETMOUSEPOS
 FUNCTION J-GETMOUSEBUTTON
 FUNCTION J-FOCUSLISTENER
 FUNCTION J-COMPONENTLISTENER
 FUNCTION J-WINDOWLISTENER
 FUNCTION J-SETFLOWLAYOUT
 FUNCTION J-SETBORDERLAYOUT
 FUNCTION J-SETGRIDLAYOUT
 FUNCTION J-SETFIXLAYOUT
 FUNCTION J-SETNOLAYOUT
 FUNCTION J-SETBORDERPOS
 FUNCTION J-SETHGAP
 FUNCTION J-SETVGAP
 FUNCTION J-SETINSETS
 FUNCTION J-SETALIGN
 FUNCTION J-SETFLOWFILL
 FUNCTION J-TRANSLATE
 FUNCTION J-CLIPRECT
 FUNCTION J-DRAWRECT
 FUNCTION J-FILLRECT
 FUNCTION J-DRAWROUNDRECT
 FUNCTION J-FILLROUNDRECT
 FUNCTION J-DRAWOVAL
 FUNCTION J-FILLOVAL
 FUNCTION J-DRAWCIRCLE
 FUNCTION J-FILLCIRCLE
 FUNCTION J-DRAWARC
 FUNCTION J-FILLARC
 FUNCTION J-DRAWLINE
 FUNCTION J-DRAWPOLYLINE
 FUNCTION J-DRAWPOLYGON
 FUNCTION J-FILLPOLYGON
 FUNCTION J-DRAWPIXEL
 FUNCTION J-DRAWSTRING
 FUNCTION J-SETXOR
 FUNCTION J-GETIMAGE
 FUNCTION J-GETIMAGESOURCE
 FUNCTION J-DRAWIMAGESOURCE
 FUNCTION J-GETSCALEDIMAGE
 FUNCTION J-DRAWIMAGE
 FUNCTION J-DRAWSCALEDIMAGE
 FUNCTION J-SETCOLOR
 FUNCTION J-SETCOLORBG
 FUNCTION J-SETNAMEDCOLOR
 FUNCTION J-SETNAMEDCOLORBG
 FUNCTION J-LOADIMAGE
 FUNCTION J-SAVEIMAGE
 FUNCTION J-SYNC
 FUNCTION J-BEEP
 FUNCTION J-RANDOM
 FUNCTION J-SLEEP
*> intrinsic functions
 FUNCTION ALL INTRINSIC.
