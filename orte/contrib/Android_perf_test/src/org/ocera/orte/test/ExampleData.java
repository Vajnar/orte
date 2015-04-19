package org.ocera.orte.test;

import org.ocera.orte.*;
import org.ocera.orte.types.*;

public class ExampleData extends MessageData {
  public short data = 1;

  public ExampleData(DomainApp domainApp, String newTopic) {
    super();
    this.setTopic(newTopic);
    domainApp.regNewDataType("example_type",
      getMaxDataLength());
  }

  @Override
  public void write() {
    buffer.rewind();
    buffer.putShort(this.data);
  }

  @Override
  public void read() {
    buffer.rewind();
    this.data = buffer.getShort();
  }

  @Override
  public int getMaxDataLength() {
    return ORTEConstant.SHORT_FIELD_SIZE;
  }
}
