function showTemporaryText(imageElement, text, position) {
    const tooltip = document.createElement('div');
    tooltip.classList.add('tooltip');
    tooltip.textContent = text;

    document.body.appendChild(tooltip);

    const rect = imageElement.getBoundingClientRect();
    
    if (position === 'right') {
        tooltip.style.left = `${rect.right + window.scrollX + 10}px`;
        tooltip.style.top = `${rect.top + window.scrollY}px`;
    } else if (position === 'left') {
        tooltip.style.left = `${rect.left + window.scrollX - tooltip.offsetWidth - 10}px`;
        tooltip.style.top = `${rect.top + window.scrollY}px`;
    }

    setTimeout(() => {
        tooltip.remove();
    }, 2000);
}