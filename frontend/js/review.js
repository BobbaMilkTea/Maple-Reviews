const theirNameField = document.querySelector('#theirNameField')
const typeDropdown = document.querySelector('#typeDropdown')
const roleDropdown = document.querySelector('#roleDropdown')
const specificsDropdown = document.querySelector('#specificsDropdown')
const detailsDiv = document.querySelector('#detailsDiv')
const promisedField = document.querySelector('#promised')
const actualField = document.querySelector('#actual')
const priceField = document.querySelector('#price')

const leechBuyerSpecifics = ['-Buyer options-', 'EPM', 'Levels']
const leechSellerSpecifics = ['-Seller options-', 'Payment']

function setDropdownOptions(dropdown, options) {
    const optionID = '#' + dropdown.id + ' option'
    document.querySelectorAll(optionID).forEach(o => o.remove());
    let isFirst = true
    for (const option of options) {
        var opElement = document.createElement('option')
        opElement.text = opElement.value = option
        if (isFirst) {
            opElement.disabled = 'true'
            opElement.selected = 'selected'
            isFirst = false
        }
        dropdown.add(opElement, -1)
    }
}

function displaySpecifics() {
    detailsDiv.style.display = 'none'
    switch (typeDropdown.value + roleDropdown.value) {
        case 'LeechBuyer':
            setDropdownOptions(specificsDropdown, leechBuyerSpecifics)
            break
        case 'LeechSeller':
            setDropdownOptions(specificsDropdown, leechSellerSpecifics)
    }
}

function displayDetails(arg) {
    promisedField.placeholder = 'Promised ' + arg.value
    actualField.placeholder = 'Actual ' + arg.value
    detailsDiv.style.display = 'block'
}

function submitReview(event) {
    const requiredFields = [
        { input: [theirNameField], message: 'Name is required' },
        { input: [typeDropdown, roleDropdown], message: 'Service type and role are required' },
        { input: [specificsDropdown], message: 'Specifics are required' },
        { input: [promisedField, actualField], message: 'Promised and actual values are required' },
        { input: [priceField], message: 'Price is required' }
    ]
    let valid = true
    requiredFields.forEach(field => {
        valid = requireValue(field.input, field.message)
    })
    if (!valid) {
        event.preventDefault()
    }
}

document.querySelector('#reviewForm').addEventListener('submit', submitReview)
