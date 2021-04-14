const {
  getDevices,
  getStorage,
  getRecursiveItems,
  mapItem,
} = require('./utils');

const addItem = (label, message) => {
  const resultEl = document.getElementById('result');
  const itemEl = document.createElement('li');
  itemEl.innerHTML = `<span class="label">${label}</span>`;
  if (message)
    itemEl.innerHTML += `<span class="message">${JSON.stringify(
      message,
      null,
      2
    )}</span>`;
  resultEl.appendChild(itemEl);
};

(async () => {
  addItem('read devices...');
  const devices = await getDevices();
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
    console.log('rootItems', rootItems);
    const t1 = performance.now();
    console.info(
      `Call to getRecursiveItems took ${Math.floor(
        (t1 - t0) / 1000
      )} milliseconds.`
    );
    const drawTree = node => {
      const children = node.children ? node.children.map(mapItem) : [];
      const files = children.filter(f => f.type === 'file');
      const folders = children.filter(f => f.type === 'folder');
      if (!folders.length) return `${files.map(f => `<li>${f.name}</li>`)}`;

      let html = [];
      for (let folder of folders) {
        const subtree = drawTree(folder);
        html.push(`<li>${folder.name}\n${subtree}</li>`);
      }
      return html.length ? `<ul>${html.join('')}</ul>` : '';
    };

    document.getElementById('tree').innerHTML = drawTree(rootItems[0]);

    const getFileList = (node, path) => {
      let result = {};
      const children = node.children || [];
      children.forEach(item => {
        const currentPath = `${path}/${item.name}`;
        result[currentPath] = {
          ...item,
          fullPath: currentPath,
        };
        if (item.type === 'folder') {
          const subResult = getFileList(item, currentPath);
          result = {
            ...result,
            ...subResult,
          };
        }
      });
      delete node.children;
      return result;
    };

    console.log(
      'getFileList',
      getFileList(rootItems[0], `{${storage.name}}/${rootItems[0].name}`)
    );
  }
})();
