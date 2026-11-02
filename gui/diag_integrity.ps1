Add-Type @"
using System;using System.Text;using System.Runtime.InteropServices;
public class TG {
 [DllImport("advapi32.dll", SetLastError=true)] public static extern bool OpenProcessToken(IntPtr p, uint acc, out IntPtr tok);
 [DllImport("advapi32.dll", SetLastError=true)] public static extern bool GetTokenInformation(IntPtr tok, int cls, IntPtr buf, int len, out int ret);
 [DllImport("kernel32.dll")] public static extern IntPtr OpenProcess(uint acc, bool inh, uint pid);
 [DllImport("kernel32.dll")] public static extern bool CloseHandle(IntPtr h);
 [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
 [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
 public delegate bool EnumProc(IntPtr h, IntPtr l);
 [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
 public static IntPtr Find(string prefix){
   IntPtr f=IntPtr.Zero;
   EnumWindows(delegate(IntPtr h, IntPtr l){
     var sb=new StringBuilder(300); GetWindowText(h,sb,300);
     if(f==IntPtr.Zero && sb.ToString().StartsWith(prefix)) f=h;
     return true;
   }, IntPtr.Zero);
   return f;
 }
 public static string Integrity(uint pid){
   IntPtr ph=OpenProcess(0x0400, false, pid);
   if(ph==IntPtr.Zero) return "OpenProcess fail " + Marshal.GetLastWin32Error();
   IntPtr tok;
   if(!OpenProcessToken(ph,0x0008,out tok)){ CloseHandle(ph); return "OpenProcessToken fail " + Marshal.GetLastWin32Error(); }
   int len=0;
   GetTokenInformation(tok,25,IntPtr.Zero,0,out len);
   IntPtr buf=Marshal.AllocHGlobal(len);
   int ret=0;
   bool ok=GetTokenInformation(tok,25,buf,len,out ret);
   string res="fail";
   if(ok){ int rid=Marshal.ReadInt32(buf,8); res="RID=0x"+rid.ToString("X")+" "; if(rid>=0x4000) res+="SYSTEM"; else if(rid>=0x3000) res+="HIGH(admin)"; else if(rid>=0x2000) res+="MEDIUM"; else res+="LOW"; }
   Marshal.FreeHGlobal(buf); CloseHandle(tok); CloseHandle(ph);
   return res;
 }
}
"@
$e=[TG]::Find("Nextion Editor")
$p0=[uint32]0
[void][TG]::GetWindowThreadProcessId($e,[ref]$p0)
"editor pid=$p0 integrity=" + [TG]::Integrity($p0)
"this pid=$PID integrity=" + [TG]::Integrity([uint32]$PID)
"qoder pid=11768 integrity=" + [TG]::Integrity(11768)
