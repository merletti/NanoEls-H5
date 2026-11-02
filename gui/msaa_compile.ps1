param([string]$name="Compile")
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
using System.Collections.Generic;

public static class MSAA {
  [DllImport("oleacc.dll")] public static extern int AccessibleObjectFromWindow(IntPtr hwnd, uint id, ref Guid iid, [MarshalAs(UnmanagedType.IUnknown)] out object ppvObject);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
  [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  public static IntPtr Find(string prefix){
    IntPtr res = IntPtr.Zero;
    EnumWindows(delegate(IntPtr h, IntPtr l){
      if(res == IntPtr.Zero && IsWindowVisible(h)){
        var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
        if(sb.ToString().StartsWith(prefix)){ res = h; return false; }
      }
      return true;
    }, IntPtr.Zero);
    return res;
  }
  public static object From(IntPtr h){
    Guid g = new Guid("618736E0-3C3D-11CF-810C-00AA00389B71");
    object o; int hr = AccessibleObjectFromWindow(h, 0xFFFFFFFC, ref g, out o);
    if(hr != 0) throw new Exception("AccessibleObjectFromWindow hr=" + hr);
    return o;
  }
  public static List<string> Walk(object acc, int depth, string target, List<object> hits){
    var list = new List<string>();
    var a = (Accessibility.IAccessible)acc;
    int n = 0; try { n = a.accChildCount; } catch {}
    for(int i=1;i<=n;i++){
      object ch = null;
      try { ch = a.get_accChild(i); } catch { }
      if(ch == null){
        string nm = ""; try { nm = a.get_accName(i); } catch {}
        object role = null; try { role = a.get_accRole(i); } catch {}
        string desc = ""; try { desc = a.get_accDescription(i); } catch {}
        if(nm != null && nm.Length > 0){
          list.Add(new string(' ', depth) + nm + " role=" + role);
          if(nm.IndexOf(target, StringComparison.OrdinalIgnoreCase) >= 0){
            hits.Add(a); hits.Add(i);
          }
        }
      } else {
        list.Add(new string(' ', depth) + "<child>");
        list.AddRange(Walk(ch, depth+2, target, hits));
      }
    }
    return list;
  }
}
"@ -ReferencedAssemblies Accessibility
$h = [MSAA]::Find("Nextion Editor")
if($h -eq [IntPtr]::Zero){ "editor non trovato"; exit 1 }
$acc = [MSAA]::From($h)
$ia = [Accessibility.IAccessible]$acc
"root name: " + $ia.get_accName(0)
$hits = New-Object System.Collections.Generic.List[object]
$lines = [MSAA]::Walk($acc, 0, $name, $hits)
$lines | Select-Object -First 120
"hits: " + ($hits.Count/2)
for($i=0;$i -lt $hits.Count;$i+=2){
  $a = $hits[$i]; $idx = $hits[$i+1]
  try { "name: " + $a.get_accName($idx) + " role: " + $a.get_accRole($idx) } catch {}
  try { $a.accDoDefaultAction($idx); "default action invoked" } catch { "action failed: " + $_.Exception.Message }
}
