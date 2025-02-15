import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.image.RescaleOp;
import java.util.Scanner;
import javax.swing.*;

public class GraphicSystem extends JFrame {
	
	private JLabel imgPanel;
	private QueueADT<String> imageFilenames;
	private StackADT<GSOperation> operations;
	
	public GraphicSystem () {
		super();
		
		init();
		
		setSize(600, 500);
		imgPanel = new JLabel();
		nextImage();
		add(imgPanel);
		setVisible(true);
	}
	
	private void init () {
		imageFilenames = new LinkedQueue<String>();
		imageFilenames.enqueue("mountain.jpg");
		imageFilenames.enqueue("vangogh.jpg");
		imageFilenames.enqueue("car.jpg");
		imageFilenames.enqueue("pizza.jpg");
		imageFilenames.enqueue("music.jpg");
		
		operations = new ArrayStack<GSOperation>();
	}
	
	/**
	 * This method will brighten the image. The code was taken from:
	 * http://www.java2s.com/example/java-utility-method/swing-icon/changebrightness-icon-icon-float-factor-448ec.html
	 */
	private void changeBrightness (float amount) {
		ImageIcon icon = (ImageIcon)imgPanel.getIcon();
		BufferedImage bi = new BufferedImage(icon.getIconWidth(), icon.getIconHeight(), BufferedImage.TYPE_INT_ARGB);
		bi.getGraphics().drawImage(icon.getImage(), 0, 0, icon.getImageObserver());
		RescaleOp op = new RescaleOp(amount, 0, null);
		bi = op.filter(bi, bi);
		ImageIcon newIcon = new ImageIcon();
		newIcon.setImage(bi);
		imgPanel.setIcon(newIcon);
	}
	private void brighten () {
		saveCurrentState();
		changeBrightness(1.5f);
	}
	
	private void darken () {
		saveCurrentState();
		changeBrightness(0.5f);
	}

	private void nextImage () {
		saveCurrentState();
		String imgFile = imageFilenames.dequeue();
		changeImage(imgFile);
		imageFilenames.enqueue(imgFile);
	}
	
	private void saveCurrentState () {
		operations.push(new GSOperation(imgPanel.getIcon(), imageFilenames));
	}
	
	private void changeImage (String imgFile) {
		ImageIcon icon = new ImageIcon(imgFile);
		Image img = icon.getImage();
		Image scaledImg = img.getScaledInstance(550, 450, Image.SCALE_SMOOTH);
		ImageIcon newIcon = new ImageIcon(scaledImg);
		imgPanel.setIcon(newIcon);
	}
	
	private void undo () {
		if (operations.isEmpty()) System.out.println("No operation to undo.");
		else {
			Icon lastIcon = operations.pop().getImage();
			imageFilenames = operations.pop().getImageQueue();
			imgPanel.setIcon(lastIcon); // Set the previous state's image into the panel.
			saveCurrentState();
		}
	}
	
	private void run () {
		Scanner input = new Scanner(System.in);
		String inputText = "";
		boolean running = true;
		
		while (running) {
			String text = "Enter a valid command\t'dark', 'bright', 'next', 'undo', or 'quit'";
			System.out.println(text);
			inputText = input.next();
			
			if (inputText.equals("dark")) {
				darken();
			} else if (inputText.equals("bright")) {
				brighten();
			} else if (inputText.equals("next")) {
				nextImage();
			} else if (inputText.equals("undo")) {
				undo();
			} else if (inputText.equals("quit")) {
				running = false;
			} else {
				System.out.println("Unknown command: " + inputText);
			}
			
		}
		input.close();
	}

	public static void main(String[] args) {
		
		GraphicSystem gs = new GraphicSystem();
		gs.run();
		
	}

}
