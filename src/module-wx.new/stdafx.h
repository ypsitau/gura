#ifndef __STDAFX_H__
#define __STDAFX_H__
#include <gura.h>
#define LPCTSTR LPCWSTR
#define LPFINDREPLACE LPFINDREPLACEW
#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/aboutdlg.h>
#include <wx/accel.h>
#include <wx/access.h>
#include <wx/event.h>
#include <wx/animate.h>
#include <wx/app.h>
#include <wx/apptrait.h>
#include <wx/archive.h>
#include <wx/dynarray.h>
#include <wx/arrstr.h>
#include <wx/artprov.h>
#include <wx/aui/dockart.h>
#include <wx/aui/auibook.h>
#include <wx/aui/aui.h>
#include <wx/bitmap.h>
#include <wx/bmpcbox.h>
#include <wx/bmpbuttn.h>
#include <wx/dataobj.h>
#include <wx/sizer.h>
#include <wx/brush.h>
#include <wx/gdicmn.h>
#include <wx/dcbuffer.h>
#include <wx/stream.h>
#include <wx/utils.h>
#include <wx/busyinfo.h>
#include <wx/button.h>
#include <wx/laywin.h>
#include <wx/calctrl.h>
#include <wx/caret.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/choice.h>
#include <wx/choicebk.h>
#include <wx/object.h>
#include <wx/ipc.h>
#include <wx/dcclient.h>
#include <wx/clntdata.h>
#include <wx/clipbrd.h>
#include <wx/cmdline.h>
#include <wx/collpane.h>
#include <wx/colour.h>
#include <wx/cmndata.h>
#include <wx/colordlg.h>
#include <wx/clrpicker.h>
#include <wx/combobox.h>
#include <wx/combo.h>
#include <wx/cmdproc.h>
#include <wx/config.h>
#include <wx/cshelp.h>
#include <wx/control.h>
#include <wx/ctrlsub.h>
#include <wx/strconv.h>
#include <wx/cursor.h>
#include <wx/socket.h>
#include <wx/datstrm.h>
#include <wx/dataview.h>
#include <wx/dateevt.h>
#include <wx/datectrl.h>
#include <wx/datetime.h>
//#include <wx/db.h>
//#include <wx/dbtable.h>
//#include <wx/dbgrid.h>
#include <wx/dc.h>
#include <wx/memory.h>
#include <wx/debugrpt.h>
#include <wx/renderer.h>
#include <wx/dialog.h>
#include <wx/dialup.h>
#include <wx/dir.h>
#include <wx/dirdlg.h>
#include <wx/filepicker.h>
#include <wx/display.h>
#include <wx/dynlib.h>
#include <wx/docview.h>
#include <wx/docmdi.h>
#include <wx/dragimag.h>
#include <wx/dnd.h>
#include <wx/encconv.h>
#include <wx/ffile.h>
#include <wx/wfstream.h>
#include <wx/file.h>
#include <wx/fileconf.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/filesys.h>
#include <wx/mimetype.h>
#include <wx/fdrepdlg.h>
#include <wx/font.h>
#include <wx/fontdlg.h>
#include <wx/fontenum.h>
#include <wx/fontmap.h>
#include <wx/fontpicker.h>
#include <wx/frame.h>
#include <wx/protocol/ftp.h>
#include <wx/gauge.h>
#include <wx/gbsizer.h>
#include <wx/gdiobj.h>
#include <wx/dirctrl.h>
#include <wx/valgen.h>
#include <wx/glcanvas.h>
#include <wx/graphics.h>
#include <wx/grid.h>
#include <wx/generic/gridctrl.h>
#include <wx/hashmap.h>
#include <wx/hashset.h>
#include <wx/hash.h>
#include <wx/help.h>
#include <wx/html/htmlcell.h>
#include <wx/html/htmprint.h>
#include <wx/html/htmlfilt.h>
#include <wx/html/helpctrl.h>
#include <wx/html/helpdata.h>
#include <wx/html/helpdlg.h>
#include <wx/html/helpfrm.h>
#include <wx/html/helpwnd.h>
#include <wx/htmllbox.h>
#include <wx/html/htmlpars.h>
#include <wx/html/htmltag.h>
#include <wx/html/winpars.h>
#include <wx/html/htmlwin.h>
#include <wx/protocol/http.h>
#include <wx/hyperlink.h>
#include <wx/icon.h>
#include <wx/iconloc.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/layout.h>
#include <wx/joystick.h>
#include <wx/list.h>
#include <wx/listbook.h>
#include <wx/listbox.h>
#include <wx/listctrl.h>
#include <wx/intl.h>
#include <wx/log.h>
#include <wx/longlong.h>
#include <wx/mdi.h>
#include <wx/mediactrl.h>
#include <wx/buffer.h>
#include <wx/dcmemory.h>
#include <wx/fs_mem.h>
#include <wx/mstream.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/msgdlg.h>
#include <wx/metafile.h>
#include <wx/minifram.h>
#include <wx/dcmirror.h>
#include <wx/module.h>
#include <wx/choicdlg.h>
#include <wx/notebook.h>
#include <wx/odcombo.h>
#include <wx/printdlg.h>
#include <wx/palette.h>
#include <wx/panel.h>
#include <wx/textdlg.h>
#include <wx/filefn.h>
#include <wx/pen.h>
#include <wx/pickerbase.h>
#include <wx/platinfo.h>
#include <wx/dcps.h>
#include <wx/power.h>
#include <wx/print.h>
#include <wx/dcprint.h>
#include <wx/process.h>
#include <wx/progdlg.h>
#include <wx/propdlg.h>
#include <wx/protocol/protocol.h>
#include <wx/quantize.h>
#include <wx/radiobox.h>
#include <wx/radiobut.h>
#include <wx/recguard.h>
#include <wx/regex.h>
#include <wx/region.h>
#include <wx/richtext/richtextbuffer.h>
#include <wx/richtext/richtextstyles.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextformatdlg.h>
#include <wx/richtext/richtextprint.h>
#include <wx/richtext/richtexthtml.h>
#include <wx/richtext/richtextstyledlg.h>
#include <wx/richtext/richtextxml.h>
#include <wx/sashwin.h>
#include <wx/ptr_scpd.h>
#include <wx/dcscreen.h>
#include <wx/scrolbar.h>
#include <wx/scrolwin.h>
#include <wx/srchctrl.h>
#include <wx/snglinst.h>
#include <wx/slider.h>
#include <wx/sckstrm.h>
#include <wx/sound.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splash.h>
#include <wx/splitter.h>
#include <wx/stackwalk.h>
#include <wx/stdpaths.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/stopwatch.h>
#include <wx/textctrl.h>
#include <wx/stc/stc.h>
#include <wx/string.h>
#include <wx/sstream.h>
#include <wx/tokenzr.h>
#include <wx/richtext/richtextsymboldlg.h>
#include <wx/sysopt.h>
#include <wx/settings.h>
#include <wx/tarstrm.h>
#include <wx/taskbar.h>
#include <wx/sckipc.h>
#include <wx/textfile.h>
#include <wx/txtstrm.h>
#include <wx/valtext.h>
#include <wx/timer.h>
#include <wx/tipdlg.h>
#include <wx/tipwin.h>
#include <wx/tglbtn.h>
#include <wx/toolbar.h>
#include <wx/toolbook.h>
#include <wx/tooltip.h>
#include <wx/toplevel.h>
#include <wx/treebook.h>
#include <wx/treectrl.h>
#include <wx/treebase.h>
#include <wx/uri.h>
#include <wx/url.h>
#include <wx/validate.h>
#include <wx/variant.h>
#include <wx/vlbox.h>
#include <wx/vscroll.h>
#include <wx/window.h>
#include <wx/wupdlock.h>
#include <wx/wizard.h>
#include <wx/xml/xml.h>
#include <wx/xrc/xmlres.h>
#include <wx/zipstrm.h>
#if defined(__WXMSW__)
#include <wx/thread.h>
#include <wx/dde.h>
#include <wx/msw/registry.h>
#include <wx/msw/ole/activex.h>
#include <wx/msw/ole/automtn.h>
#endif
#include <wx/numdlg.h>
#include <wx/stockitem.h>
#include <wx/zstream.h>

#include "module-wx.h"
#include "class/Classes.h"
#include "Class_wx_EventFactory.h"
#include "CArray.h"

#endif