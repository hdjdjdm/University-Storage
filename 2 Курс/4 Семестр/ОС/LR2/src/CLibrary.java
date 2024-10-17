import com.sun.jna.Library;
import com.sun.jna.Pointer;


interface CLibrary extends Library {
    int PTRACE_ATTACH = 16;
    //команда подключения
    int PTRACE_DETACH = 17;
    //команда отключения
    int PTRACE_PEEKDATA = 2;
    //команда получения данных
    int PTRACE_POKEDATA = 5;

    //команда записи данных
    int ptrace(int request, int pid, Pointer addr, int data);
}