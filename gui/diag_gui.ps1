Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class GI {
 [StructLayout(LayoutKind.Sequential)] public struct GUITHREADINFO {
   public int cbSize; public uint flags; public IntPtr hwndActive; public IntPtr hwndFocus;
   public IntPtr hwndCapture; public IntPtr hwndMenuOwner; public IntPtr hwndMoveSize; public IntPtr hwndCaret;
   public int left; public int top; public int right; public int bottom;
 }
 [DllImport("user32.dll")] public static extern bool GetGUIThreadInfo(uint tid, ref GUITHREADINFO g);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 public static string Dump(uint tid){
   var g=new GUITHREADINFO(); g.cbSize=Marshal.SizeOf(typeof(GUITHREADINFO));
   bool ok=GetGUIThreadInfo(tid, ref g);
   return String.Format("ok={0} flags=0x{1:X} active={2} focus={3} capture={4} menuowner={5} movesize={6} caret={7}",
     ok,g.flags,g.hwndActive,g.hwndFocus,g.hwndCapture,g.hwndMenuOwner,g.hwndMoveSize,g.hwndCaret);
 }
}
"@
$fg=[GI]::GetForegroundWindow()
$p0=[uint32]0
$tid=[GI]::GetWindowThreadProcessId($fg,[ref]$p0)
"fg=$fg tid=$tid pid=$p0"
[GI]::Dump($tid)
"tid 9064 (editor): " + [GI]::Dump(9064)
