import org.ocera.orte.*;
import org.ocera.orte.types.*;

public class ExampleSubscriber extends SubscriptionCallback {

  static int count = 0;

  public static void main(String[] args) throws Exception {
    NtpTime deadline = new NtpTime(10);
    NtpTime minSeparation = new NtpTime(0);

    DomainApp appDomain = new DomainApp(
      0, DomainProp.defaultPropsCreate(), null, false);
    ExampleData datamsg = new ExampleData(appDomain, "example_topic");
    SubsProp subProps = new SubsProp(
      "example_topic", "example_type",
      minSeparation, deadline,
      ORTEConstant.IMMEDIATE,
      ORTEConstant.STRICT_RELIABLE, 0);
    long startTime = System.nanoTime();
    Subscription sub = appDomain.
      createSubscription(subProps, datamsg, new ExampleSubscriber());

    while(count < 10001) {
      Thread.sleep(50);
    }
    long endTime = System.nanoTime();

    System.out.println("Count: " + count + "\nElapsed time: " + (endTime-startTime));

    sub.destroy();
    appDomain.destroy();
  }

  public void callback(RecvInfo info, MessageData msg) {
    if (info.getRecvStatus() == ORTEConstant.NEW_DATA)
      count++;
  }
}
