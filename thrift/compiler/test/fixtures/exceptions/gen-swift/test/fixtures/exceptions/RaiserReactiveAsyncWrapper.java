/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

package test.fixtures.exceptions;

import java.util.*;

public class RaiserReactiveAsyncWrapper 
  implements Raiser.Async {
  private Raiser.Reactive _delegate;

  public RaiserReactiveAsyncWrapper(Raiser.Reactive _delegate) {
    
    this._delegate = _delegate;
  }

  @java.lang.Override
  public void close() {
    _delegate.close();
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<Void> doBland() {
      return com.facebook.swift.transport.util.FutureUtil.toListenableFuture(_delegate.doBland());
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<Void> doRaise() {
      return com.facebook.swift.transport.util.FutureUtil.toListenableFuture(_delegate.doRaise());
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<String> get200() {
      return com.facebook.swift.transport.util.FutureUtil.toListenableFuture(_delegate.get200());
  }

  @java.lang.Override
  public com.google.common.util.concurrent.ListenableFuture<String> get500() {
      return com.facebook.swift.transport.util.FutureUtil.toListenableFuture(_delegate.get500());
  }

}
