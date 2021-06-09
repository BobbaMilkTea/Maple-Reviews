const profileName = document.querySelector('#profileName')
const profileScore = document.querySelector('#profileScore')
const profileNumReviews = document.querySelector('#profileNumReviews')
const profileReviews = document.querySelector('#profileReviews')

function displayProfile() {
    profileName.innerText = sessionStorage.getItem('name')
    profileScore.innerText = sessionStorage.getItem('score')
    profileNumReviews.innerText = sessionStorage.getItem('numReviews')

    while(profileReviews.rows.length > 1) {
        profileReviews.deleteRow(-1)
    }

    const reviews = JSON.parse(sessionStorage.getItem('reviews'))
    for(const review of reviews) {
        var newRow = profileReviews.insertRow(-1)
        var newText = document.createTextNode(review['type'])
        newRow.insertCell().appendChild(newText)
        newText = document.createTextNode(review['promised'])
        newRow.insertCell().appendChild(newText)
        newText = document.createTextNode(review['actual'])
        newRow.insertCell().appendChild(newText)
        newText = document.createTextNode(review['price'])
        newRow.insertCell().appendChild(newText)
        newText = document.createTextNode(review['description'].replace(/[+]/g, ' '))
        newRow.insertCell().appendChild(newText)
        var dateObj = new Date(review['timestamp'] * 1000)
        newText = document.createTextNode(dateObj.toDateString())
        newRow.insertCell().appendChild(newText)
    }
}

displayProfile()