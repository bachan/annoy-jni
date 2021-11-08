package com.spotify.annoy.jni.base;

import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class AnnoyIndexRefCount {
  private AnnoyIndex ann;
  private AtomicInteger refCount = new AtomicInteger(0);

  public AnnoyIndexRefCount(AnnoyIndex ann) {
    this.ann = ann;
  }

  public List<Integer> getNearestByVector(List<Float> vector, int nbNeighbors) {
    refCount.incrementAndGet();
    List<Integer> result = ann.getNearestByVector(vector, nbNeighbors);
    refCount.decrementAndGet();
    return result;
  }

  public List<Integer> getNearestByVector(List<Float> vector, int nbNeighbors, int searchK) {
    refCount.incrementAndGet();
    List<Integer> result = ann.getNearestByVector(vector, nbNeighbors, searchK);
    refCount.decrementAndGet();
    return result;
  }

  public List<Integer> getNearestByItem(int item, int nbNeighbors) {
    refCount.incrementAndGet();
    List<Integer> result = ann.getNearestByItem(item, nbNeighbors);
    refCount.decrementAndGet();
    return result;
  }

  public List<Integer> getNearestByItem(int item, int nbNeighbors, int searchK) {
    refCount.incrementAndGet();
    List<Integer> result = ann.getNearestByItem(item, nbNeighbors, searchK);
    refCount.decrementAndGet();
    return result;
  }

  public List<Float> getItemVector(int item) {
    refCount.incrementAndGet();
    List<Float> result = ann.getItemVector(item);
    refCount.decrementAndGet();
    return result;
  }

  public float getDistance(int itemA, int itemB) {
    refCount.incrementAndGet();
    float result = ann.getDistance(itemA, itemB);
    refCount.decrementAndGet();
    return result;
  }

  public int size() {
    refCount.incrementAndGet();
    int result = ann.size();
    refCount.decrementAndGet();
    return result;
  }

  // NOTE: this will block the thread until it can release the mmap-ed resources
  public void close() {
    while (refCount.get() > 0) {
      try {
        Thread.sleep(5000L);
      } catch (Exception e) {
        // do nothing
      }
    }
    ann.close();
  }
}
