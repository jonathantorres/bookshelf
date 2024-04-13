import java.io.*;

class Help {
    String helpfile;

    Help(String fname) {
        helpfile = fname;
    }

    boolean helpOn(String what) {
        int ch;
        String topic;
        String info;

        try (BufferedReader helpRdr = new BufferedReader(new FileReader(helpfile))) {
            do {
                ch = helpRdr.read();

                if (ch == '#') {
                    topic = helpRdr.readLine();
                    if (what.compareTo(topic) == 0) {
                        do {
                            info = helpRdr.readLine();
                            if (info != null) {
                                System.out.println(info);
                            }
                        } while ((info != null) && (info.compareTo("") != 0));
                        return true;
                    }
                }
            } while (ch != -1);
        } catch(IOException exc) {
            System.out.println("Error accessing help file");
            return false;
        }
        return false;
    }

    String getSelection() {
        String topic = "";
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         System.out.print("Enter topic: ");
         try {
            topic = br.readLine();
         } catch(IOException exc) {
            System.out.println("Error reading console");
         }
         return topic;
    }
}

class FileHelp {
    public static void main(String[] args) {
        Help hlpobj = new Help("helpfile.txt");
        String topic;

        System.out.println("Try the help system. Enter 'stop' to end");
        do {
            topic = hlpobj.getSelection();
            if (!hlpobj.helpOn(topic)) {
                if (topic.compareTo("stop") != 0) {
                    System.out.println("Topic not found!\n");
                }
            }
        } while (topic.compareTo("stop") != 0);
    }
}
