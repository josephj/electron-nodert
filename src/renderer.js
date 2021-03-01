const { getDevices, getStorage, getRecursiveItems, mapItem } = require('./utils');

const addItem = (label, message) => {
  const resultEl = document.getElementById('result');
  const itemEl = document.createElement('li');
  itemEl.innerHTML = `<span class="label">${label}</span>`;
  if (message) itemEl.innerHTML += `<span class="message">${JSON.stringify(message, null, 2)}</span>`;
  resultEl.appendChild(itemEl);
}


(async () => {
  addItem('read devices...');
  const devices = await getDevices()
  addItem('devices: ', devices);
  for (let device of devices) {
    addItem('read storage...');
    const storage = await getStorage(device.deviceId);
    addItem('storage: ', {
      dateCreated: storage.dateCreated,
      displayName: storage.displayName,  
      displayType: storage.displayType,  
      folderRelativeId: storage.folderRelativeId,
      name: storage.name,
      path: storage.path,
    });
    console.log('storage :', storage);

   const t0 = performance.now();
   const rootItems = await getRecursiveItems(storage);
   const t1 = performance.now();
   console.info(`Call to getRecursiveItems took ${Math.floor((t1 - t0) / 1000)} milliseconds.`); 
    const drawTree = (node) => {
      const children = node.children ? node.children.map(mapItem) : [];
      const files = children.filter(f => f.type === 'file');
      const folders = children.filter(f => f.type === 'folder');
      if (!folders.length) return `${files.map(f => `<li>${f => f.name}</li>`)}`;

      let html = [];
      for (let folder of folders) {
        const subtree = drawTree(folder);
        html.push(`<li>${folder.name}\n${subtree}</li>`);
      }
      return html.length ? `<ul>${html.join('')}</ul>`: '';
    }

    document.getElementById('tree').innerHTML = drawTree(rootItems[0]);
  }
})();
