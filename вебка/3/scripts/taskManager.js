function deleteTask(index) {
    const tasks = JSON.parse(localStorage.getItem('tasks')) || [];
    tasks.splice(index, 1);
    localStorage.setItem('tasks', JSON.stringify(tasks));
    loadTasks();
}

function addTask(event) {
    event.preventDefault();
    const taskName = document.getElementById('taskName').value.trim();
    if (taskName === '') {
        alert('Пожалуйста, введите название задачи!');
        return;
    }
    const tasks = JSON.parse(localStorage.getItem('tasks')) || [];

    const taskExists = tasks.some(task => task.text.toLowerCase() === taskName.toLowerCase());

    if (taskExists) {
        alert('Задача с таким названием уже существует!');
    } else {
        tasks.push({ text: taskName, isChecked: false, column: 'taskList' });
        localStorage.setItem('tasks', JSON.stringify(tasks));

        window.location.href = 'tasks.html';
    }
}

const addTaskForm = document.getElementById('addTaskForm');
if (addTaskForm) {
    addTaskForm.addEventListener('submit', addTask);
}

function toggleCheck(event) {
    const index = event.target.dataset.index;
    const tasks = JSON.parse(localStorage.getItem('tasks')) || [];
    
    tasks[index].isChecked = !tasks[index].isChecked;
    localStorage.setItem('tasks', JSON.stringify(tasks));

    const taskElement = event.target.closest('.task');

    if (tasks[index].isChecked) {
        taskElement.classList.add('checked');
    } else {
        taskElement.classList.remove('checked');
    }
}

let draggedTaskIndex;

function allowDrop(event) {
    event.preventDefault();
}

function drag(event) {
    draggedTaskIndex = event.target.dataset.index;
}

function drop(event) {
    event.preventDefault();

    const targetColumn = event.target.closest('td').id;
    
    const tasks = JSON.parse(localStorage.getItem('tasks')) || [];

    if (draggedTaskIndex !== undefined && targetColumn) {
        tasks[draggedTaskIndex].column = targetColumn;
        localStorage.setItem('tasks', JSON.stringify(tasks));

        loadTasks();
    }
}
