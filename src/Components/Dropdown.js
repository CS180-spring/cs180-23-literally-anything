import React, { useState } from 'react';
import './Dropdown.css';
import { Button } from './Button';


export const Dropdown = () => {
  const [dropdownValue, setDropdownValue] = useState('');
  const [listItems, setListItems] = useState([]);

  const handleDropdownChange = (event) => {
    setDropdownValue(event.target.value);
  };

  const handleButtonClick = () => {
    if (dropdownValue !== '') {
      setListItems([...listItems, dropdownValue]);
      setDropdownValue('');
    }
  };

  return (
    <div>
      <select value={dropdownValue} onChange={handleDropdownChange}>
        <option value="">Select an item</option>
        <option value="Item 1">Item 1</option>
        <option value="Item 2">Item 2</option>
        <option value="Item 3">Item 3</option>
      </select>
      <button onClick={handleButtonClick}>Add Item</button>
      <ul>
        {listItems.map((item, index) => (
          <li key={index}>{item}</li>
        ))}
      </ul>
    </div>
  );
}

