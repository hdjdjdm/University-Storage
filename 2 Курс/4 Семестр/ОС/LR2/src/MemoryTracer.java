import com.sun.jna.Native;
import com.sun.jna.Pointer;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryTracer {
    long address;
    int pid;
    CLibrary libc = (CLibrary) Native.loadLibrary("/lib/x86_64-linux-gnu/libc.so.6", CLibrary.class);
    public MemoryTracer(int pid, String adrStr){
        this.pid = pid;
        address = Long.parseLong(adrStr, 16);
    }

    public String read(){
        byte[] bytes = new byte[1024];
        boolean flag = true;
        int counter = 0;

        if (libc.ptrace(CLibrary.PTRACE_ATTACH, pid, null, 0) < 0){
            System.out.println("Huinya heppen");
        }

        while (flag){
            long addressValue = libc.ptrace(CLibrary.PTRACE_PEEKDATA, pid, Pointer.createConstant(address), 0);
            for (int i = 0; i < 8; i++){
                bytes[(counter * 8) + i] = (byte) (addressValue >>> (i*8)&0xFF);
                if (bytes[(counter * 8) + i] == '\0'){
                    flag = false;
                    break;
                }
            }
            address += 8;
            counter++;
        }

        libc.ptrace(CLibrary.PTRACE_DETACH, pid, null, 0);
        return new String(bytes).trim();
    }
    public void write(String value){
        boolean flag = true;
        byte[] stringBytes = value.getBytes(StandardCharsets.UTF_8);
        byte[] bytes = new byte[1024];
        int counter = 0;
        int endMemCellIndex = -1;

        if (libc.ptrace(CLibrary.PTRACE_ATTACH, pid, null, 0) < 0){
            System.out.println("Huinya heppen");
        }

        while (flag){
            long addressValue = libc.ptrace(CLibrary.PTRACE_PEEKDATA, pid, Pointer.createConstant(address), 0);
            for (int i = 0; i < 8; i++){
                bytes[(counter * 8) + i] = (byte) (addressValue >>> (i*8)&0xFF);
                if (bytes[(counter * 8) + i] == '\0'){
                    endMemCellIndex = (counter * 8) + i;
                    flag = false;
                    break;
                }
            }
            if (counter * 8 >= stringBytes.length - 1)
                break;
            byte[] tmpStrBytes = {32, 32, 32, 32, 32, 32, 32, 32};
            for (int k = 0; k < 8; k++){
                try{
                    tmpStrBytes[k] = stringBytes[(counter * 8) + k];
                } catch (IndexOutOfBoundsException ex){
                    flag = false;
                    break;
                }
            }
            if (endMemCellIndex != -1){
                tmpStrBytes[endMemCellIndex % 8] = (byte) '\0';
                flag = false;
            }
            endMemCellIndex = -1;

            reverse(tmpStrBytes);
            ByteBuffer bb = ByteBuffer.wrap(tmpStrBytes);
            libc.ptrace(CLibrary.PTRACE_POKEDATA, pid, Pointer.createConstant(address), (int) bb.getLong());
            address += 8;
            counter++;
        }
        libc.ptrace(CLibrary.PTRACE_DETACH, pid, null,0);
    }

    public static void reverse(byte[] array) {
        if (array == null) {
            return;
        }
        int i = 0;
        int j = array.length - 1;
        byte tmp;
        while (j > i) {
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            j--;
            i++;
        }
    }
}
