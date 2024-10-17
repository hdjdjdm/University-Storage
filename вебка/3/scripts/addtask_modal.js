const openDialogButton = document.getElementById('openDialog');
const taskDialog = document.getElementById('taskDialog');
const closeDialogButton = document.getElementById('closeDialog');

openDialogButton.addEventListener('click', () => {
    taskDialog.showModal();
    document.body.style.overflow = 'hidden';
    document.body.classList.add('modal-open');
});

closeDialogButton.addEventListener('click', () => {
    taskDialog.close();
    document.body.style.overflow = 'auto';
    document.body.classList.remove('modal-open');
});

taskDialog.addEventListener('click', (event) => {
    if (event.target === taskDialog) {
        taskDialog.close();
        document.body.style.overflow = 'auto';
        document.body.classList.remove('modal-open');
    }
});
