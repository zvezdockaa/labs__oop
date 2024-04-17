function changePage(tag) {
    let lists = document.getElementsByTagName(tag);
    for (let i = 0; i < lists.length; i++) {
      let items = lists[i].getElementsByTagName('li');
      let vlojList = lists[i].querySelector('ul, ol');
      if (items.length > 0 && !vlojList) {
        let firstItem = items[0];
        let lastItem = items[items.length - 1];
        let temp = document.createElement('li');
        lastItem.parentNode.insertBefore(temp, lastItem);
        firstItem.parentNode.insertBefore(lastItem, firstItem);
        temp.parentNode.insertBefore(firstItem, temp);
        temp.parentNode.removeChild(temp);
      }
    }
  }
  changePage('ul');
  