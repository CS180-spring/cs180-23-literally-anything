import React, { useState } from 'react';
import { Button } from './Button';
import axios from 'axios';

const TextBox = () => {
  const [isOpen, setIsOpen] = useState(false);
  const [userInput, setUserInput] = useState('');

  const handleButtonClick = () => {
    setIsOpen(true);
        // Perform the API request here
  };

  const handleInputChange = (event) => {
    setUserInput(event.target.value);
  };

  const handleFormSubmit = (event) => {
    event.preventDefault();
    // You can store the user input in a state variable or perform any desired actions here.
    console.log('User input:', userInput);
    setIsOpen(false);
    axios.post('https://54.177.181.151:4000/createDB', { data: userInput })
    .then(response => {
      // Handle the response if needed
      console.log(response);
    })
    .catch(error => {
      // Handle errors if any
      console.error(error);
    });  
  };

  return (
    <div>

    <div className="button">
      {Button && <Button buttonStyle='btn--outline' buttonSize='btn--large' onClick={handleButtonClick}> Create Database
      </Button>}
      {isOpen && (
        <form onSubmit={handleFormSubmit}>
          <input type="text" value={userInput} onChange={handleInputChange} />
          <Button buttonStyle = 'btn--outline' buttonSize='btn--medium'  type="submit" >
            Submit New Database
          </Button>
        </form>
      )}
    </div>

      {/* <button onClick={handleButtonClick}>Open Text Input</button> */}
      {/* {isOpen && (
        <form onSubmit={handleFormSubmit}>
          <input type="text" value={userInput} onChange={handleInputChange} />
          <button type="submit">Submit</button>
        </form>
      )} */}
    </div>
  );
};

export default TextBox;