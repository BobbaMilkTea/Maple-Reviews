const playerNameField = document.querySelector('#playerNameField')
const queryResultTable = document.querySelector('#queryResult')

function displayQueryResult(data) {
    while(queryResultTable.rows.length > 1) {
        queryResultTable.deleteRow(-1)
    }
    for(const profile of data) {
        var newRow = queryResultTable.insertRow(-1)
        
        //insert link
        var profileButton = document.createElement("button")
        profileButton.addEventListener('click', queryProfile)
        profileButton.textContent = profile['ign']
        newRow.insertCell().appendChild(profileButton)

        newText = document.createTextNode(profile['score'])
        newRow.insertCell().appendChild(newText)
        newText = document.createTextNode(profile['numReviews'])
        newRow.insertCell().appendChild(newText)
    }
}

async function queryProfileList(event) {
    event.preventDefault()
    const requiredFields = [
        { input: [playerNameField], message: 'Name is required' }
    ]
    let valid = true
    requiredFields.forEach(field => {
        valid = requireValue(field.input, field.message)
    })
    if (!valid) {
        return
    }
    const uri = 'http://127.0.1.1:8080/?playerNameField=' + playerNameField.value
    fetch(uri, { method: 'GET' })
    .then(response => response.json())
    .then(data => {displayQueryResult(data['searchResult'])})
}

async function queryProfile(event) {
    event.preventDefault()
    const uri = 'http://127.0.1.1:8080/?playerName=' + this.textContent
    console.log(uri)
    fetch(uri, { method: 'GET' })
    .then(response => response.json())
    .then(data => console.log(data))
}

document.querySelector('#queryForm').addEventListener('submit', queryProfileList)
