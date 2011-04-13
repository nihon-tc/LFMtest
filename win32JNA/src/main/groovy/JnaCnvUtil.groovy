import com.sun.jna.*;
import com.sun.jna.ptr.*;
import com.sun.jna.win32.*;
import java.nio.*;

class JnaCnvUtil {
    public static String ByteByReference2String(ByteByReference ref) {
        return ref.getPointer().getString(0);
    }
    
    //String <=> Pointer
    public static Pointer String2Pointer(String source) {
        return new NativeString(source).getPointer();
    }

    public static String Pointer2String(Pointer source) {
        return source.getString(0);
    }

    //Integer <=> IntByReference
    public static IntByReference Integer2IntByReference(Integer source) {
        return new IntByReference(source);
    }

    public static Integer IntByReference2Integer(IntByReference source) {
        return source.getValue();
    }

    //String[] <=> Pointer
    public static Pointer StringList2Pointer(List<String> source) {
            String[] sourceStrings = source.toArray(new String[0]);
            StringArray stringArray = new StringArray(sourceStrings);
            return stringArray.share(0);
    }

    public static List<String> Pointer2StringList(Pointer source, final int size) {
            List<String> result = new ArrayList<String>();
            Pointer[] pList = source.getPointerArray(0, size);
            for( Pointer p : pList) {
                     String value = p.getString(0);
                     result.add(value);
            }
            return result;
    }

    //IntBuffer <=> int[]
    public static IntBuffer IntegerList2IntBuffer(List<Integer> source) {
            Integer[] sourceIntegers = source.toArray(new Integer[0]);
            IntBuffer result = IntBuffer.allocate(source.size());
            result.put(sourceIntegers);
            return result;
    }

    public static List<Integer> IntBuffer2IntegerList(IntBuffer source, final int size) {
            List<Integer> result = new ArrayList<Integer>()
            for(int i=0;i<size;i++){
                result.add source.get(i) 
            }
            return result
    }

    //IntBuffer <=> int[][]
    public static List<List<Integer>> Array2IntegerTableList(int[][] source,final int rowsize){
            List<List<Integer>> result = new ArrayList<ArrayList<Integer>>();
            for(int i=0;i < rowsize ; i++){
                def list = new ArrayList<Integer>();
                list.addAll(source[i]);
                result.add(list);
            }
            return result;
    }

    public static IntBuffer IntegerTableList2IntBuffer(List<List<Integer>> source) {
            List<Integer>[] sourceIntegerTableLists = source.toArray(new ArrayList<Integer>[0]);
            IntBuffer result = IntBuffer.allocate(source.size() * source.get(0).size());
            for( List<Integer> sourceIntegerLists : sourceIntegerTableLists) {
                    int length = sourceIntegerLists.size();
                    Integer[] sourceIntegers = sourceIntegerLists.toArray(new Integer[0]);
                    for( Integer it : sourceIntegers) {
                        result.put(it);
                    }
            }
            return result;
    }

    public static List<List<Integer>> IntBuffer2IntegerTableList(IntBuffer source, final int rowsize ,final int colsize) {
            List<List<Integer>> result = new ArrayList<ArrayList<Integer>>();
            int offset = 0;
            for(int i=0;i < rowsize ; i++){
                def list = new ArrayList<Integer>();
                for(int j =offset;j < offset + colsize ;j++){
                    list.add source.get(j);
                }
                result.add(list);
                offset += colsize;
            }
            return result;
    }
}

