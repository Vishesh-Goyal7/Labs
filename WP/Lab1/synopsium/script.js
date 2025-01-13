/* script.js */
function showTab(tabName) {
    // Hide all tabs
    const tabs = document.querySelectorAll('.tab-content');
    tabs.forEach(tab => tab.style.display = 'none');

    // Deactivate all buttons
    const buttons = document.querySelectorAll('.tab-button');
    buttons.forEach(button => button.classList.remove('active'));

    // Show the selected tab and activate the corresponding button
    document.getElementById(tabName).style.display = 'block';
    document.getElementById(tabName + 'Tab').classList.add('active');
}

function switchToForm(eventName) {
    // Show the form tab and pre-fill the event dropdown
    showTab('form');
    document.getElementById('event').value = eventName;
}

function validateForm() {
    const email = document.getElementById('email').value;
    const mobile = document.getElementById('mobile').value;

    // Ensure email and mobile fields are filled
    if (!email || !mobile) {
        alert('Email and Mobile Number are required!');
        return false;
    }
    alert('Form submitted successfully!');
    return true;
}

// Default to the "Info" tab on page load
document.addEventListener('DOMContentLoaded', () => showTab('info'));
