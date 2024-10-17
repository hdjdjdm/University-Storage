//num 1
restoreNamePlaceholder();

function clearNamePlaceholder() {
    var input = document.getElementById('name');
    if (input.value === 'например, Иванов') {
        input.value = '';
    }
}

function restoreNamePlaceholder() {
    var input = document.getElementById('name');
    if (input.value === '') {
        input.value = 'например, Иванов';
    }
}

//num 2
function checkID() {
    var input = document.getElementById('id').value;
    if (isNaN(input) || input.trim() === '') {
        alert('ID не является числом');
        return false;
    }
    return true;
}

//num 3
document.addEventListener('DOMContentLoaded', function() {
    var deleteLinks = document.querySelectorAll('tbody a[href^="/deleteEmployee"]');

    deleteLinks.forEach(function(link) {
        link.addEventListener('click', function(event) {
            event.preventDefault();

            var deleteUrl = this.getAttribute('href');
            var employeeId = deleteUrl.split('/').pop();

            if (confirm('Вы точно хотите удалить сотрудника №' + employeeId + '?')) {
                var row = this.closest('tr')
                if (row) {
                    row.remove();
                }
            }            
        })
    }) 
})

//num 4
function submitName() {
    var name = document.getElementById('name').value;
    localStorage.setItem('name', name);
    window.location.href = 'searchByName.html';
}