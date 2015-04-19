import org.ocera.orte.*;
import org.ocera.orte.types.*;

public class ExamplePublisher {

   public static void main(String[] args) throws Exception {
    NtpTime persistence = new NtpTime(3);
    int strength = 100;

    DomainApp appDomain = new DomainApp(
      0, DomainProp.defaultPropsCreate(), null, false);
    ExampleData datamsg = new ExampleData(appDomain, "example_topic");
    PublProp publProp = new PublProp("example_topic",
      "example_type", persistence, strength);
    publProp.setReliabilityOffered(ORTEConstant.STRICT_RELIABLE);
    Publication pub = appDomain.createPublication(publProp, datamsg);

    while(true) {
      pub.send(datamsg);
      datamsg.data++;
    }
  }
}
