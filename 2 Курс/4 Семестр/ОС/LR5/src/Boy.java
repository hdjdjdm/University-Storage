class Boy extends Thread {
    public Boy(String name){
        super(name);
    }

    public void run(){
        try {
            Deadlock.boyMethod();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
