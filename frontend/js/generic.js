function error(input, message) {
    input.nextElementSibling.nextElementSibling.className = 'error'
    input.nextElementSibling.nextElementSibling.innerText = message
    return false
}

function success(input) {
    input.className = 'success'
    input.nextElementSibling.nextElementSibling.innerText = ''
    return true
}

function requireValue(input, message) {
    var lastElement = input.slice(-1)[0]
    for(const element of input) {
        if(element.value.trim() === '' || element.value[0] == '-') {
            return error(lastElement, message)
        }
    }
    return success(lastElement)
}