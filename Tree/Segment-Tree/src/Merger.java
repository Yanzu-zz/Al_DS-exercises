public interface Merger<E> {
    E merge(E a, E b); // merge 传入的 a和b，然后返回去
}
