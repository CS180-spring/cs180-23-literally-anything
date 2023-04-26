import './App.css';
import { Routes, Route, HashRouter } from 'react-router-dom';
import Home from './Pages/Home'
import CreateDataBase from './Pages/CreateDataBase'
import NoPage from './Pages/NoPage';


function App() {


  return (
    <div className="App">
      <HashRouter>
        <Routes>
          <Route index element={<Home />} />
          <Route path="/home" element={<Home />} />
          <Route path="/createDataBase" element={<CreateDataBase />} />
          <Route path="*" element={<NoPage />} />
        </Routes>
      </HashRouter>

    </div>
  );
}

export default App;
