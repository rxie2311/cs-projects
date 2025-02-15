import javax.swing.Icon;
import javax.swing.ImageIcon;

public class GSOperation {

	private ImageIcon savedStateImage;
	private QueueADT<String> imageQueue;
	
	public GSOperation (Icon img, QueueADT<String> queue) {
		savedStateImage = (ImageIcon)img;
		// Make a clone of the parameter queue into the imageQueue parameter.
		imageQueue = new LinkedQueue<String>();
		for (int i = 0; i < queue.size(); i++) {
			String tmp = queue.dequeue();
			queue.enqueue(tmp);
			imageQueue.enqueue(tmp);
		}
	}
	
	public ImageIcon getImage () {
		return savedStateImage;
	}
	
	public QueueADT<String> getImageQueue () {
		return imageQueue;
	}
	
}
