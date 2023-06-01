import React, { useState, useEffect } from "react";
import axios from "axios";
import { useNavigate, Link, useLocation } from 'react-router-dom';
import TextBoxSearch from '../Components/TextBoxSearch';
import { type } from "@testing-library/user-event/dist/type";


const Search = ({ object }) => {
    const [text, setText] = useState(JSON.stringify(object, null, 2));
    const navigate = useNavigate();
    const location = useLocation();
    const [searchResults, setsearchResults] = useState();

    //console.log();
  

    return (
        <div className='Search'>
            <div className='container'>
    
            <div className="left-collumn">
                <h1>ReactDB</h1>
            </div>
    
            <div className='main_content'>
              <div className="edit_container">
              <div className="search_container">
                
              </div>
              
             
              </div>
            </div>
        
            </div>
        </div>
      );
}

export default Search;
