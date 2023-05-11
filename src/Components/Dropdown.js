import React, { useState } from 'react';
import './Dropdown.css';
import { Button } from './Button';

export const Dropdown =()=> {
    const [state, setstate] = useState(false);
    const showDropdown=()=> {
        setstate(true);
    }
    const hideDropdown=()=> {
        setstate(false);
    }
    return (
        <div className="dropdown">
            <div classNmae="dropdown-menu" onMouseEnter={showDropdown} onMouseLeave={hideDropdown}>
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

