/* script.js */
const popupData = {
    mobile1: {
        image: 'p1.jpeg',
        name: 'Iphone 12',
        specs: {
            "Screen": "6.5-inch AMOLED",
            "Battery": "5000mAh",
            "Camera": "64MP + 8MP + 5MP",
            "Processor": "Snapdragon 865",
            "Price": "$499"
        }
    },
    mobile2: {
        image: 'p2.jpeg',
        name: 'Samsung S23',
        specs: {
            "Screen": "6.5-inch AMOLED",
            "Battery": "5000mAh",
            "Camera": "64MP + 8MP + 5MP",
            "Processor": "Snapdragon 865",
            "Price": "$499"
        }
    },
    mobile3: {
        image: 'p3.jpeg',
        name: 'Iphone 16',
        specs: {
            "Screen": "6.5-inch AMOLED",
            "Battery": "5000mAh",
            "Camera": "64MP + 8MP + 5MP",
            "Processor": "Snapdragon 865",
            "Price": "$499"
        }
    }
};

function showPopup(id) {
    const popup = document.getElementById('popup');
    const details = popupData[id];
    const popupDetails = document.getElementById('popup-details');
    
    let specsHTML = '<table><tbody>';
    for (const [key, value] of Object.entries(details.specs)) {
        specsHTML += `<tr><td><strong>${key}</strong></td><td>${value}</td></tr>`;
    }
    specsHTML += '</tbody></table>';
    
    popupDetails.innerHTML = `
        <img src="${details.image}" alt="${details.name}" style="width: 100%; max-width: 300px; margin: 10px auto;">
        <h3>${details.name}</h3>
        ${specsHTML}
    `;
    
    popup.style.display = 'flex';
}

function closePopup() {
    const popup = document.getElementById('popup');
    popup.style.display = 'none';
}

// Close the popup if clicked outside the popup content
document.getElementById('popup').addEventListener('click', (event) => {
    const popupContent = document.querySelector('.popup-content');
    if (!popupContent.contains(event.target)) {
        closePopup();
    }
});
