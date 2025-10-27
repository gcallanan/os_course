/**
 * Educational program demonstrating Process Contention Scope (PCS) with Java Virtual Threads.
 * 
 * This program creates 8 virtual threads, each performing CPU-intensive busy work for approximately
 * 5 seconds. Virtual threads are scheduled on a limited pool of platform (OS) threads, demonstrating
 * how the JVM scheduler manages contention when multiple virtual threads compete for carrier threads.
 * 
 * By setting -Djdk.virtualThreadScheduler.parallelism=2, only 2 platform threads are used to carry
 * all 8 virtual threads, illustrating process contention scope where thread scheduling occurs at
 * the application level (within the JVM) rather than at the kernel level.
 * 
 * Expected behavior: Virtual threads will complete over time as they share the limited carrier threads,
 * with completion times showing the effects of scheduling and CPU contention.
 * 
 * Compile with: javac ch5p2_JavaVirtualThreads.java
 * Run with: java -Djdk.virtualThreadScheduler.parallelism=2 ch5p2_JavaVirtualThreads.java
 */

import java.util.ArrayList;
import java.util.List;

public class ch5p2_JavaVirtualThreads {
    public static void main(String[] args) throws Exception {
        int numThreads = 8;
        long startNano = System.nanoTime(); // capture once in main

        List<Thread> vts = new ArrayList<>(numThreads);
        for (int i = 0; i < numThreads; i++) {
            final int id = i;
            Thread t = Thread.startVirtualThread(busyTask(id, 5_000_000_000L, startNano)); // ~5s
            vts.add(t);
        }

        for (Thread t : vts)
            t.join();
        System.out.println("All done.");
    }

    // Builds the Runnable that a virtual thread will run
    private static Runnable busyTask(int id, long durationNanos, long startNano) {
        return () -> {
            long end = System.nanoTime() + durationNanos;
            long x = 0;

            // Busy work (no blocking)
            while (System.nanoTime() < end) {
                x += 0x9E3779B97F4A7C15L;
                x ^= (x >>> 27);
                x *= 0x94D049BB133111EBL;
                Thread.onSpinWait(); // non-blocking hint
            }

            long elapsedMs = (System.nanoTime() - startNano) / 1_000_000L;
            System.out.printf("VT-%02d done at ~%d ms\n",
                    id, elapsedMs, x, Thread.currentThread());
        };
    }
}
