class Girl extends Thread {
    public Girl(String name){
        super(name);
    }

    public void run(){
        try {
            Deadlock.girlMethod();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
