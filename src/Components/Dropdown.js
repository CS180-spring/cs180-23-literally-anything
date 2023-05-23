import React, { useState, useEffect } from 'react';
import './Dropdown.css';
import { Button } from './Button';
import axios from 'axios';

export const Dropdown =()=> {
    const [state, setstate] = useState(false);
    const showDropdown=()=> {
        setstate(true);
    }
    const hideDropdown=()=> {
        setstate(false);
    }
const [data, setData] = useState([]);

    useEffect(() => {
        axios.get('https://54.177.181.151:4000/listDBs')
          .then(response => {
            setData(response.data);
          })
          .catch(error => {
            console.log(error);
          });
      }, []);

    return (
        <div className="dropdown">
            <div className="dropdown-menu" onMouseEnter={showDropdown} onMouseLeave={hideDropdown}>
                DataBase:
                {state ?(<ul className="dropdown-list" onMouseEnter={showDropdown}>
                    <li>
                        <div className="button">
                            {Button && <Button buttonStyle='btn--outline' buttonSize='btn--small'> Collection 1
                            </Button>}
                        </div>
                    </li>
                    <li>
                        <div className="button">
                            {Button && <Button buttonStyle='btn--outline' buttonSize='btn--small'> Collection 2
                            </Button>}
                        </div>
                    </li>
                    <li>
                        <div className="button">
                            {Button && <Button buttonStyle='btn--outline' buttonSize='btn--small'> Collection 3
                            </Button>}
                        </div>
                    </li>
                    <li>
                        <div className="button">
                            {Button && <Button buttonStyle='btn--outline' buttonSize='btn--small'> Collection 4
                            </Button>}
                        </div>
                    </li>
                </ul>):
                null}
            </div>
        </div>
    )
}

