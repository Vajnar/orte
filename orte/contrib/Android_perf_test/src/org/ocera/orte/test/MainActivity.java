package org.ocera.orte.test;

import org.ocera.orte.DomainApp;
import org.ocera.orte.Manager;
import org.ocera.orte.Publication;
import org.ocera.orte.Subscription;
import org.ocera.orte.SubscriptionCallback;
import org.ocera.orte.types.DomainProp;
import org.ocera.orte.types.MessageData;
import org.ocera.orte.types.NtpTime;
import org.ocera.orte.types.ORTEConstant;
import org.ocera.orte.types.PublProp;
import org.ocera.orte.types.RecvInfo;
import org.ocera.orte.types.SubsProp;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView text;
	Button btn1, btn2, btn3;
	
  class ExamplePublisher implements Runnable {
	  
    public void run() {
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
  
  class ExampleCallback extends SubscriptionCallback {
	    int count = 0;
	    
	    public void callback(RecvInfo info, MessageData msg) {
	        if (info.getRecvStatus() == ORTEConstant.NEW_DATA)
	          count++;
	      }
  }
  
  class ExampleSubscriber implements Runnable {

  public void run() {
      NtpTime deadline = new NtpTime(10);
      NtpTime minSeparation = new NtpTime(0);
      ExampleCallback callback = new ExampleCallback();

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
        createSubscription(subProps, datamsg, callback);

      while(callback.count < 10001) {
        try {
			Thread.sleep(50);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
      }
      long endTime = System.nanoTime();

      System.out.println("Count: " + callback.count + "\nElapsed time: " + (endTime-startTime));

      sub.destroy();
      appDomain.destroy();
    }
  }
  
  class ExampleManager implements Runnable {

	  public void run() {
	    Manager manager = new Manager();
	    try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	  }
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		text = (TextView)this.findViewById(R.id.text);
		btn1 = (Button)this.findViewById(R.id.button1);
		btn2 = (Button)this.findViewById(R.id.button2);
		btn3 = (Button)this.findViewById(R.id.button3);
		
		btn1.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View arg0) {
				(new Thread(new ExamplePublisher())).start();
			}
		});
		
		btn3.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View arg0) {
				(new Thread(new ExampleSubscriber())).start();
			}
		});
		
		btn2.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View arg0) {
				(new Thread(new ExampleManager())).start();
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
